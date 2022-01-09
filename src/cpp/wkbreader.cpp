#include "wkbreader.hpp"
#include <sstream>

WKBReader::WKBReader() {
    _reader = GEOSWKBReader_create();
}

WKBReader::~WKBReader() {
    if (_reader) {
        GEOSWKBReader_destroy(_reader);
        _reader = NULL;
    }
}

Persistent<Function> WKBReader::constructor;

void WKBReader::Initialize(Handle<Object> target)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, WKBReader::New);
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->SetClassName(String::NewFromUtf8(isolate, "WKBReader"));

    NODE_SET_PROTOTYPE_METHOD(tpl, "readHEX", WKBReader::ReadHEX);

    constructor.Reset(isolate, tpl->GetFunction());

    target->Set(String::NewFromUtf8(isolate, "WKBReader"), tpl->GetFunction());
}

void WKBReader::New(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    WKBReader *wkbReader = new WKBReader();
    wkbReader->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
}

void WKBReader::ReadHEX(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    WKBReader* reader = ObjectWrap::Unwrap<WKBReader>(args.This());
    String::Utf8Value hex(args[0]->ToString());
    std::string str = std::string(*hex);
//    std::istringstream is( str );
    try {
        GEOSGeometry* geom = GEOSWKBReader_readHEX(reader->_reader, reinterpret_cast<const unsigned char *>(str.c_str()), str.length());
        args.GetReturnValue().Set(Geometry::New(geom));
    } catch (...) {
        isolate->ThrowException(Exception::Error(String::NewFromUtf8(isolate, "Exception while reading WKB.")));
    }
}
