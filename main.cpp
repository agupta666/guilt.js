#include <v8.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "types.h"

using namespace v8;

HValue g_log(const Arguments& args) {

	if (args.Length() != 1 ) {
		return v8::ThrowException(v8::String::New("Bad parameters"));
	}

	UTF8StringValue value(args[0]);
	std::cout << *value << std::endl;

	return v8::Undefined();
}


HString v8string(std::string s) {
	return v8::String::New(s.c_str(), s.length());
}


PersistentContext createContext() {
	ObjTemplate global = ObjectTemplate::New();
	global->Set(v8string("log"), FunctionTemplate::New(g_log));

	return v8::Context::New(NULL, global);
}

HString readSource(char *fileName) {
	std::fstream ifs(fileName);
	std::ostringstream ss;
	char line[512];
	while( ifs.getline(line, 512) ) {
		ss << line << std::endl;
	}

	return v8::String::New(ss.str().c_str(), ss.str().length());
}

void executeScript(HString source, HString name) {

	HandleScope scope;
	HScript script = Script::Compile(source, name);
	
	HValue result = script->Run();

	if( !result->IsUndefined()) {
		UTF8StringValue svalue(result);
		std::cout << *svalue << std::endl;
	}
}

int main(int argc, char* argv[]) {
	
	HandleScope hScope;
	PersistentContext ctx = createContext();
	
	if (ctx.IsEmpty()) {
		std::cerr << "ERROR: Failed to create context" << std::endl;
		return 1;
	}

	ctx->Enter();
	HString source = readSource(argv[1]);
	// Execute the script here ....

	executeScript(source, v8string(argv[1]));
	
	ctx->Exit();
	ctx.Dispose();
	v8::V8::Dispose();

	return 0;
}
