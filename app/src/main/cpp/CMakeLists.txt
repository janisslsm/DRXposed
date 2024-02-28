cmake_minimum_required(VERSION 3.22.1)

project("DRXposed")
set(CMAKE_CXX_STANDARD 20)

include_directories(dependencies/lua)

add_definitions(
        -DLUA_USE_DLOPEN
        -DLUA_USE_POSIX
)

add_library( lua STATIC
        dependencies/lua/lapi.c
        dependencies/lua/lauxlib.c
        dependencies/lua/lbaselib.c
        dependencies/lua/lcode.c
        dependencies/lua/ldblib.c
        dependencies/lua/ldebug.c
        dependencies/lua/ldo.c
        dependencies/lua/ldump.c
        dependencies/lua/lfunc.c
        dependencies/lua/lgc.c
        dependencies/lua/linit.c
        dependencies/lua/liolib.c
        dependencies/lua/llex.c
        dependencies/lua/lmathlib.c
        dependencies/lua/lmem.c
        dependencies/lua/loadlib.c
        dependencies/lua/lobject.c
        dependencies/lua/lopcodes.c
        dependencies/lua/loslib.c
        dependencies/lua/lparser.c
        dependencies/lua/lstate.c
        dependencies/lua/lstring.c
        dependencies/lua/lstrlib.c
        dependencies/lua/ltable.c
        dependencies/lua/ltablib.c
        dependencies/lua/ltm.c
        dependencies/lua/luac.c
        dependencies/lua/lundump.c
        dependencies/lua/lvm.c
        dependencies/lua/lzio.c
        dependencies/lua/print.c
        )

add_library(
        DRXposed
        SHARED
        utils/utils.cpp
        core.cpp
        )

find_library(log-lib log)

target_link_libraries(DRXposed lua ${log-lib})
