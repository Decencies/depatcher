
#include "Hooks.h"
#include "Global.h"
#include "Depatcher.h"

#include "ReflectiveDLLInjection.h"

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
    if (dwReason == DLL_QUERY_HMODULE && lpReserved != nullptr) {
        *(HMODULE *) lpReserved = Global::hInstance;
    }
    if (dwReason == DLL_PROCESS_ATTACH) {
        Global::hInstance = hInstance;
        Depatcher::Init();
    }
    return TRUE;
}