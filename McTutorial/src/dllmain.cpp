#include <windows.h>
#include <iostream>
#include <jni.h>
#include "../sdk/sdk.h"
#include "srg/automapper.h"
#include "srg/mappings.h"

DWORD WINAPI mainThread(HMODULE hModule) {
	jsize count;
	if (JNI_GetCreatedJavaVMs(&sdk->vm, 1, &count) != JNI_OK || count == 0) {
		MessageBoxA(0, "JavaVM not found.", "LCF", 0);
		return 0;
	}

	jint res = sdk->vm->GetEnv((void**)&sdk->env, JNI_VERSION_1_6);
	if (res == JNI_EDETACHED)
		res = sdk->vm->AttachCurrentThread((void**)&sdk->env, nullptr);

	if (res != JNI_OK) {
		MessageBoxA(0, "Could not create a java environnement.", "LCF", 0);
		return 0;
	}

	if (sdk->env != nullptr) {
		automapper->init();
		mappings->init();

		while (!GetAsyncKeyState(VK_END))
		{
			if (!sdk->init()) {
				MessageBoxA(0, "Failed Initialization.", "LCF", 0);
			}

			Sleep(20);
		}
		FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);
	}
	else {
		MessageBoxA(0, "Could not create a java environnement.", "LCF", 0);
		FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);
		return 0;
	}

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  dwReason, LPVOID lpReserved) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		if (auto thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(mainThread), hModule, 0, nullptr); thread != nullptr) {
			CloseHandle(thread);
		}
	}
	return TRUE;
}
