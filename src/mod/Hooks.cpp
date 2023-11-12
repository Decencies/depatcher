#include <Hooks.h>
#include <MinHook.h>

#include <cstdio>

void Hooks::OutputDebugStringA(LPCSTR lpOutputString) {
    printf("%s", lpOutputString);
}

void Hooks::OutputDebugStringW(LPCWSTR lpOutputString) {
    printf("%ls", lpOutputString);
}

int Hooks::ProcessResponse(LPVOID, LPVOID) {
    return 0;
}

bool Hooks::Setup() {
    if (MH_Initialize() != MH_STATUS::MH_OK) {
        return !printf("Failed to initialize MinHook!\n");
    }

    bool success = false;

    success |= AddAndEnableApiNoTrampoline((LPVOID)&Hooks::OutputDebugStringA, L"kernel32.dll", "OutputDebugStringA");
    success |= AddAndEnableApiNoTrampoline((LPVOID)&Hooks::OutputDebugStringW, L"kernel32.dll", "OutputDebugStringW");
    success |= AddAndEnableNoTrampoline((LPVOID)&Hooks::ProcessResponse, (LPVOID)PROCESS_RESPONSE_ADDR);

    return success;
}

bool Hooks::AddAndEnableNoTrampoline(LPVOID pDetour, LPVOID pTarget) {
    if (MH_CreateHook(pTarget, pDetour, nullptr) != MH_STATUS::MH_OK) {
        return !printf("Failed to create hook!\n");
    }

    if (MH_EnableHook(pTarget) != MH_STATUS::MH_OK) {
        return !printf("Failed to create hook!\n");
    }

    return true;
}

bool Hooks::AddAndEnableApiNoTrampoline(LPVOID pDetour, LPCWSTR pszModule, LPCSTR pszProcName) {
    auto target = (LPVOID)GetProcAddress(GetModuleHandleW(pszModule), pszProcName);

    if (MH_CreateHookApi(pszModule, pszProcName, pDetour, nullptr) != MH_STATUS::MH_OK) {
        return !printf("Failed to create %s hook!\n", pszProcName);
    }

    if (MH_EnableHook(target) != MH_STATUS::MH_OK) {
        return !printf("Failed to enable %s hook!\n", pszProcName);
    }

    return true;
}