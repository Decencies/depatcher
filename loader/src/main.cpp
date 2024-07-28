#include <windows.h>
#include <corecrt_io.h>

#include <ios>
#include <filesystem>

#include "mod.hpp"
#include "loader/library.h"

void create_and_attach_console() {
    if (!AllocConsole()) return;

    FILE *f;

    if (freopen_s(&f, "CONOUT$", "w", stdout))
        _dup2(_fileno(stdout), 1);

    if (freopen_s(&f, "CONOUT$", "w", stderr))
        _dup2(_fileno(stdout), 2);

    std::ios::sync_with_stdio();

    SetConsoleTitle("Defiance Patcher");
}

extern "C" __declspec(dllexport) bool APIENTRY DllMain(HMODULE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason != DLL_PROCESS_ATTACH) return TRUE;

    library_init();
    create_and_attach_console();

    mod::setup();

    return TRUE;
}