#include "mod.hpp"

#include <cstdio>
#include <windows.h>

void dtr_OutputDebugStringA(LPCSTR lpOutputString) {
    printf("%s", lpOutputString);
}

void dtr_OutputDebugStringW(LPCWSTR lpOutputString) {
    printf("%ls", lpOutputString);
}

void hook_debug_outputs() {
    MH_STATUS s;
    if (!(s = MH_CreateHookApi(
            L"kernel32.dll",
            "OutputDebugStringA",
            (LPVOID) &dtr_OutputDebugStringA,
            nullptr)
    )) {
        printf("Failed to initialize OutputDebugStringA hook: %s", MH_StatusToString(s));
        return;
    }
    if (!(s = MH_CreateHookApi(
            L"kernel32.dll",
            "OutputDebugStringW",
            (LPVOID) &dtr_OutputDebugStringW,
            nullptr)
    )) {
        printf("Failed to initialize OutputDebugStringW hook: %s", MH_StatusToString(s));
        return;
    }
}

namespace game {
    const uintptr_t base_addr = 0x005A0000;
    const uintptr_t process_response_addr = base_addr + 0x625820;
}

int dtr_ProcessResponse(LPVOID, LPVOID) {
    return 0;
}

void hook_crypto_handling() {
    MH_STATUS s;
    if (!(s = MH_CreateHook(
            (LPVOID) game::process_response_addr,
            (LPVOID) &dtr_ProcessResponse,
            nullptr)
    )) {
        printf("Failed to initialize ProcessResponse hook: %s", MH_StatusToString(s));
        return;
    }
}

void mod::setup() {
    MH_STATUS s;
    if (!(s = MH_Initialize())) {
        printf("Failed to initialize MinHook: %s", MH_StatusToString(s));
        return;
    }

    hook_debug_outputs();
    hook_crypto_handling();

    if (!(s = MH_EnableHook(MH_ALL_HOOKS))) {
        printf("Failed to enable hooks: %s", MH_StatusToString(s));
        return;
    }
}