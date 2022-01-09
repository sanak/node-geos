#include "wkbwriter.hpp"

WKBWriter::WKBWriter() {
    _writer = GEOSWKBWriter_create();
}

WKBWriter::~WKBWriter() {
    if (_writer) {
        GEOSWKBWriter_destroy(_writer);
        _writer = NULL;
    }
}

Persistent<Function> WKBWriter::constructor;

void WKBWriter::Initialize(Handle<Object> target) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, WKBWriter::New);
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->SetClassName(String::NewFromUtf8(isolate, "WKBWriter"));

    NODE_SET_PROTOTYPE_METHOD(tpl, "writeHEX", WKBWriter::WriteHEX);

    constructor.Reset(isolate, tpl->GetFunction());

    target->Set(String::NewFromUtf8(isolate, "WKBWriter"), tpl->GetFunction());
}

void WKBWriter::New(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    WKBWriter* writer = new WKBWriter();
    writer->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
}

void WKBWriter::WriteHEX(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    WKBWriter *writer = ObjectWrap::Unwrap<WKBWriter>(args.This());
    Geometry *geom = ObjectWrap::Unwrap<Geometry>(args[0]->ToObject());
    //TODO catch exception?
    size_t size = 0;
    unsigned char* ret = GEOSWKBWriter_writeHEX(writer->_writer, geom->_geom, &size);
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, reinterpret_cast<const char*>(ret)));
    // TODO:
}
