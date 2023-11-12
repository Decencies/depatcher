#include <minwindef.h>

const uintptr_t BASE_ADDR = 0x005A0000;
const uintptr_t PROCESS_RESPONSE_ADDR = BASE_ADDR + 0x625820;

namespace Hooks {
    void __stdcall OutputDebugStringA(LPCSTR);
    void __stdcall OutputDebugStringW(LPCWSTR);
    int __thiscall ProcessResponse(LPVOID, LPVOID);

    bool Setup();
    bool AddAndEnableNoTrampoline(LPVOID pDetour, LPVOID pTarget);
    bool AddAndEnableApiNoTrampoline(LPVOID pDetour, LPCWSTR pszModule, LPCSTR pszProcName);
}