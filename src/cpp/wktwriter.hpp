#ifndef WKTWRITER_HPP
#define WKTWRITER_HPP

#include <geos_c.h>
#include "binding.hpp"
#include "geometry.hpp"

class WKTWriter : public ObjectWrap {

    public:
        WKTWriter();
        ~WKTWriter();
        static void Initialize(Handle<Object> target);
        static Persistent<Function> constructor;
        static void New(const FunctionCallbackInfo<Value>& args);
        static void Write(const FunctionCallbackInfo<Value>& args);

    protected:
        static void SetRoundingPrecision(const FunctionCallbackInfo<Value>& args);
        static void SetTrim(const FunctionCallbackInfo<Value>& args);

    private:
        GEOSWKTWriter* _writer;

};
#endif
