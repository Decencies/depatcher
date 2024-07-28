enable_language(ASM_MASM)

include_directories(include)

set(LOADER_SOURCES
        def/library.asm
        def/library.def
        src/main.cpp)

add_library(loader SHARED ${LOADER_SOURCES})
target_link_libraries(loader depatcher)
target_link_directories(loader PRIVATE ../libs)
set_target_properties(loader PROPERTIES OUTPUT_NAME "version")