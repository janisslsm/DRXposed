//
// Created by Janis on 17.04.2023.
//

#ifndef DRXposed_CORE_HPP
#define DRXposed_CORE_HPP
#include <cstdint>
#include <string>
extern "C" {
#include "dependencies/lua/lua.h"
#include "dependencies/lua/lualib.h"
#include "dependencies/lua/lstate.h"
#include "dependencies/lua/lapi.h"
#include "dependencies/lua/lfunc.h"
#include "dependencies/lua/lauxlib.h"
};


typedef int (*HookFunType)(void *func, void *replace, void **backup);

typedef int (*UnhookFunType)(void *func);

typedef void (*NativeOnModuleLoaded)(const char *name, void *handle);

typedef struct {
    uint32_t version;
    HookFunType hook_func;
    UnhookFunType unhook_func;
} NativeAPIEntries;

typedef NativeOnModuleLoaded (*NativeInit)(const NativeAPIEntries *entries);

#include "utils/utils.h"
#endif //DRXposed_CORE_HPP
