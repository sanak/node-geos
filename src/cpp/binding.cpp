#include "binding.hpp"
#include "wktreader.hpp"
#include "wkbreader.hpp"
#include "wktwriter.hpp"
#include "wkbwriter.hpp"
#include "geometry.hpp"
#include "geometryfactory.hpp"
#include "precisionmodel.hpp"
#include "geojsonwriter.hpp"
#include "geojsonreader.hpp"

static void
geos_msg_handler(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintf (fmt, ap);
    va_end(ap);
}

extern "C" {
    void init (Handle<Object> target) {
        initGEOS(geos_msg_handler, geos_msg_handler);

        Isolate* isolate = Isolate::GetCurrent();
        HandleScope scope(isolate);

        target->Set(String::NewFromUtf8(isolate, "geosversion"), String::NewFromUtf8(isolate, GEOSversion()));

        Geometry::Initialize(target);
        WKTReader::Initialize(target);
        WKBReader::Initialize(target);
        WKTWriter::Initialize(target);
        WKBWriter::Initialize(target);
        GeometryFactory::Initialize(target);
        PrecisionModel::Initialize(target);
        GeoJSONWriter::Initialize(target);
        GeoJSONReader::Initialize(target);
    }

    NODE_MODULE(geos, init)
}
