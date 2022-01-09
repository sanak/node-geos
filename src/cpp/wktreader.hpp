#ifndef WKTREADER_HPP
#define WKTREADER_HPP

#include <geos_c.h>
#include "binding.hpp"
#include "geometry.hpp"

class WKTReader : public ObjectWrap {

    public:
        WKTReader();
        ~WKTReader();
        static void Initialize(Handle<Object> target);
        static Persistent<Function> constructor;
        static void New(const FunctionCallbackInfo<Value>& args);
        static void Read(const FunctionCallbackInfo<Value>& args);

    protected:

    private:
        GEOSWKTReader* _reader;

};
#endif
