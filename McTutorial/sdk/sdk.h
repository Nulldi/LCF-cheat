#pragma once
#include <jni.h>

class c_sdk {
private:
	jobject array_elements;
	jclass thread_clazz;
	jobject thread;
	jclass threadgroup_clazz;
	jobject threadgroup_obj;
	jobjectArray arrayD;
public:
	JNIEnv* env;
	JavaVM* vm;

	jobject getClassLoader();
	jclass getObject(const char* className);
	bool init();
};

extern c_sdk* sdk;