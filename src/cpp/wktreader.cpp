#include "wktreader.hpp"

WKTReader::WKTReader() {
    _reader = GEOSWKTReader_create();
}

WKTReader::~WKTReader() {
    if (_reader) {
        GEOSWKTReader_destroy(_reader);
        _reader = NULL;
    }
}

Persistent<Function> WKTReader::constructor;

void WKTReader::Initialize(Handle<Object> target)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, WKTReader::New);
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->SetClassName(String::NewFromUtf8(isolate, "WKTReader"));

    NODE_SET_PROTOTYPE_METHOD(tpl, "read", WKTReader::Read);

    constructor.Reset(isolate, tpl->GetFunction());

    target->Set(String::NewFromUtf8(isolate, "WKTReader"), tpl->GetFunction());
}

void WKTReader::New(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);;

    WKTReader *wktReader = new WKTReader();
    wktReader->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
}

void WKTReader::Read(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);;

    WKTReader* reader = ObjectWrap::Unwrap<WKTReader>(args.This());
    try {
        GEOSGeometry* geom = GEOSWKTReader_read(reader->_reader, *String::Utf8Value(args[0]->ToString()));
        args.GetReturnValue().Set(Geometry::New(geom));
    } catch (...) {
        isolate->ThrowException(Exception::Error(String::NewFromUtf8(isolate, "Exception while reading WKT.")));
    }
}
