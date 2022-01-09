#include "binding.hpp"
#include "wktreader.hpp"
#include "wkbreader.hpp"
#include "wktwriter.hpp"
#include "wkbwriter.hpp"
#include "geometry.hpp"
//#include "geojsonwriter.hpp"
//#include "geojsonreader.hpp"

void geos_notice_handler(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "NOTICE: ");
    vfprintf(stderr, fmt, ap);
    va_end(ap);
}

#define ERRLEN 256

char geos_last_err[ERRLEN];

void geos_error_handler(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(geos_last_err, (size_t) ERRLEN, fmt, ap);
    va_end(ap);
}

extern "C" {
    void init (Handle<Object> target) {
        initGEOS(geos_notice_handler, geos_error_handler);

        Isolate* isolate = Isolate::GetCurrent();
        HandleScope scope(isolate);

        target->Set(String::NewFromUtf8(isolate, "geosversion"), String::NewFromUtf8(isolate, GEOSversion()));

        Geometry::Initialize(target);
        WKTReader::Initialize(target);
        WKBReader::Initialize(target);
        WKTWriter::Initialize(target);
        WKBWriter::Initialize(target);
//        GeoJSONWriter::Initialize(target);
//        GeoJSONReader::Initialize(target);
    }

    NODE_MODULE(geos, init)
}
