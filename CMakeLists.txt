cmake_minimum_required(VERSION 3.25)
project(depatcher)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -m32)

include_directories(include
        include/mod
        include/RDI
        include/RDI/inject
        include/RDI/dll)

set(RDI_inject_INCLUDES
        include/RDI/inject/GetProcAddressR.h
        include/RDI/inject/LoadLibraryR.h
        include/RDI/ReflectiveDLLInjection.h)

set(RDI_inject_SOURCES
        src/RDI/inject/GetProcAddressR.cpp
        src/RDI/inject/LoadLibraryR.cpp)

set(launcher_INCLUDES
        ${RDI_inject_INCLUDES})

set(launcher_SOURCES
        ${RDI_inject_SOURCES}
        src/launcher/WinMain.cpp)

set(RDI_dll_INCLUDES
        include/RDI/dll/ReflectiveLoader.h
        include/RDI/ReflectiveDLLInjection.h)

set(RDI_dll_SOURCES
        src/RDI/dll/ReflectiveLoader.cpp)

set(mod_INCLUDES
        ${RDI_dll_INCLUDES}
        include/mod/Global.h
        include/mod/Hooks.h
        include/mod/Depatcher.h)

set(mod_SOURCES
        ${RDI_dll_SOURCES}
        src/mod/Hooks.cpp
        src/mod/Depatcher.cpp
        src/mod/DllMain.cpp)

add_executable(depatcher ${launcher_INCLUDES} ${launcher_SOURCES})
target_link_libraries(depatcher -static gcc stdc++ winpthread -dynamic)

add_library(mod SHARED ${mod_INCLUDES} ${mod_SOURCES})
target_compile_definitions(mod PRIVATE WINVER=0x0601 _WIN32_WINNT=0x0601)
target_link_libraries(mod -static MinHook -dynamic)