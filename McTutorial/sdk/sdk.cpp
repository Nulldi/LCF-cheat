#include "sdk.h"
#include <iostream>
#include "../src/srg/mappings.h"

c_sdk* sdk = new c_sdk;

jobject c_sdk::getClassLoader()
{
	thread_clazz = env->FindClass("java/lang/Thread");
	jmethodID curthread_mid = env->GetStaticMethodID(thread_clazz, "currentThread", "()Ljava/lang/Thread;");
	thread = env->CallStaticObjectMethod(thread_clazz, curthread_mid);
	jmethodID threadgroup_mid = env->GetMethodID(thread_clazz, "getThreadGroup", "()Ljava/lang/ThreadGroup;");
	threadgroup_clazz = env->FindClass("java/lang/ThreadGroup");
	threadgroup_obj = env->CallObjectMethod(thread, threadgroup_mid);
	jmethodID groupactivecount_mid = env->GetMethodID(threadgroup_clazz, "activeCount", "()I");
	jfieldID count_fid = env->GetFieldID(threadgroup_clazz, "nthreads", "I");
	jint activeCount = env->GetIntField(threadgroup_obj, count_fid);

	arrayD = env->NewObjectArray(activeCount, thread_clazz, NULL);
	jmethodID enumerate_mid = env->GetMethodID(threadgroup_clazz, "enumerate", "([Ljava/lang/Thread;)I");
	env->CallIntMethod(threadgroup_obj, enumerate_mid, arrayD);

	array_elements = env->GetObjectArrayElement(arrayD, 0);
	jmethodID threadclassloader = env->GetMethodID(thread_clazz, "getContextClassLoader", "()Ljava/lang/ClassLoader;");

	if (threadclassloader != NULL) {
		jobject classloader_obj = env->CallObjectMethod(array_elements, threadclassloader);
		return classloader_obj;
	}
}

jclass c_sdk::getObject(const char* className) {
	jclass clazz = env->FindClass("java/lang/Class");
	jmethodID classForNameMethod = env->GetStaticMethodID(clazz, "forName", "(Ljava/lang/String;ZLjava/lang/ClassLoader;)Ljava/lang/Class;");
	if (classForNameMethod == NULL) {
		env->FatalError("Class.forName(String,boolean,java.lang.ClassLoader)java.lang.Class method not found\n");
	}

	jstring classToLoad = env->NewStringUTF(className);
	jclass jarClass = (jclass)env->CallStaticObjectMethod(clazz, classForNameMethod, classToLoad, true, getClassLoader());
	env->ReleaseStringUTFChars(classToLoad, NULL);
	return jarClass;
}

bool c_sdk::init() {
	jclass jarClass = getObject(("net.minecraft.v1_8." + mappings->class_ave).c_str());
	jmethodID getMc = env->GetStaticMethodID(jarClass, "eeeheshaeeheshssaapehaeha", ("()Lnet/minecraft/v1_8/" + mappings->class_ave + ";").c_str());
	jobject mc = env->CallStaticObjectMethod(jarClass, getMc);

	jfieldID rightClickDelayTimerFid = env->GetFieldID(env->GetObjectClass(mc), "eeaesaasahaaehsaehhephsps", "I");
	env->SetIntField(mc, rightClickDelayTimerFid, 0);

	env->DeleteLocalRef(array_elements);
	env->DeleteLocalRef(thread_clazz);
	env->DeleteLocalRef(thread);
	env->DeleteLocalRef(threadgroup_clazz);
	env->DeleteLocalRef(threadgroup_obj);
	env->DeleteLocalRef(arrayD);

	env->DeleteLocalRef(jarClass);
	env->DeleteLocalRef(mc);
	return true;
}
