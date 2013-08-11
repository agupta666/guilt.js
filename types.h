#ifndef __TYPES_H_H_
#define __TYPES_H_H_

typedef v8::Persistent<v8::Context> PersistentContext;
typedef v8::Handle<v8::ObjectTemplate> ObjTemplate ;
typedef v8::Handle<v8::String> HString;
typedef v8::Handle<v8::Script> HScript;
typedef v8::Handle<v8::Value> HValue;
typedef v8::String::Utf8Value UTF8StringValue;

#endif // __TYPES_H_H_
