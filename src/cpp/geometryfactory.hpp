#ifndef GEOMETRY_FACTORY_HPP
#define GEOMETRY_FACTORY_HPP

#include "binding.hpp"
#include "geometry.hpp"

class GeometryFactory : public ObjectWrap {

    public:
        GeometryFactory();
        ~GeometryFactory();

        static void Initialize(Handle<Object> target);
        static Persistent<Function> constructor;
        static void New(const FunctionCallbackInfo<Value>& args);

    protected:

    private:

};
#endif
