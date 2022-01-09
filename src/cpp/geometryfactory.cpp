#include "geometryfactory.hpp"

GeometryFactory::GeometryFactory() {
}

GeometryFactory::~GeometryFactory() {}

Persistent<Function> GeometryFactory::constructor;

void GeometryFactory::Initialize(Handle<Object> target) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, GeometryFactory::New);
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->SetClassName(String::NewFromUtf8(isolate, "GeometryFactory"));

    constructor.Reset(isolate, tpl->GetFunction());

    target->Set(String::NewFromUtf8(isolate, "GeometryFactory"), tpl->GetFunction());
}

void GeometryFactory::New(const FunctionCallbackInfo<Value>& args) {
    GeometryFactory* factory;
    if (args.Length() == 0) {
        factory = new GeometryFactory();
    }
    factory->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
}
