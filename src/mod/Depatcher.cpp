#include <Depatcher.h>
#include <Hooks.h>

#include <windows.h>
#include <cstdio>

void Depatcher::Init() {
    if (!SetupConsole()) {
        MessageBoxA(nullptr, "Failed to attach console!", "Error", MB_OK);
    }

    if (!Hooks::Setup()) return;

    printf("Depatcher was successfully initialized.\n");
}

bool Depatcher::SetupConsole() {
    if (AllocConsole() || AttachConsole(GetCurrentProcessId())) {
        FILE* tmp;
        freopen_s(&tmp, "CONIN$", "r", stdin);
        freopen_s(&tmp, "CONOUT$", "w", stdout);
        freopen_s(&tmp, "CONOUT$", "w", stderr);
        return true;
    }
    return false;
}