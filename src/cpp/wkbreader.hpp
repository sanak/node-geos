#ifndef WKBREADER_HPP
#define WKBREADER_HPP

#include <geos_c.h>
#include "binding.hpp"
#include "geometry.hpp"

class WKBReader : public ObjectWrap {

    public:
        WKBReader();
        ~WKBReader();
        static void Initialize(Handle<Object> target);
        static Persistent<Function> constructor;
        static void New(const FunctionCallbackInfo<Value>& args);
//        static void Read(const FunctionCallbackInfo<Value>& args);
        static void ReadHEX(const FunctionCallbackInfo<Value>& args);

    protected:

    private:
        GEOSWKBReader* _reader;

};
#endif
