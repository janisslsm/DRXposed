#include <cstring>
#include <jni.h>
#include <dlfcn.h>
#include "core.hpp"

static std::string externalFilesDir;
static HookFunType hook_func = nullptr;
static UnhookFunType unhook_func = nullptr;
lua_State* luaState;

extern "C" [[gnu::visibility("default")]] [[gnu::used]]
jint JNI_OnLoad(JavaVM *jvm, void*) {
    JNIEnv *env = nullptr;
    jvm->GetEnv((void **)&env, JNI_VERSION_1_6);

    return JNI_VERSION_1_6;
}
void* o_gettop = nullptr;
int (*backup_lua_gettop)(lua_State *L);
lua_State *(*glua_newthread) (lua_State *L);

int lua_gettop_hk(lua_State *L) {

    if(luaState == nullptr)
    {
        luaState = glua_newthread(L);
    }

    return backup_lua_gettop(L);
}

void on_library_loaded(const char *name, void *handle) {
    if (std::string(name).ends_with("liblua.so")) {
        glua_newthread = reinterpret_cast<decltype(glua_newthread)>(dlsym(handle, "lua_newthread"));

        o_gettop = dlsym(handle, "lua_gettop");
        hook_func(o_gettop, (void *) lua_gettop_hk, (void **) &backup_lua_gettop);
    }
}

extern "C" JNIEXPORT jint JNICALL Java_com_github_janisslsm_DRXposed_MainHook_loadstring(JNIEnv* env, jobject callingObject, jstring code){
    const char* c_str = env->GetStringUTFChars(code, 0);
    if(luaState != nullptr && lua_status(luaState) == 0)
    {
        luaL_loadstring(luaState, c_str);
        lua_pcall(luaState, 0, -1, 0);
    }

    env->ReleaseStringUTFChars(code, c_str);

    return 1;
}

extern "C" JNIEXPORT jint JNICALL Java_com_github_janisslsm_DRXposed_MainHook_loadfile(JNIEnv* env, jobject callingObject, jstring path){
    const char* path_c = env->GetStringUTFChars(path, 0);
    if(luaState != nullptr && lua_status(luaState) == 0)
    {
        luaL_dofile(luaState, path_c);
    }

    env->ReleaseStringUTFChars(path, path_c);

    return 1;
}

void* main_thread(void*)
{
    do {
        sleep(1);
    } while (!luaState);

    if(lua_status(luaState) == 0)
    {
        unhook_func(o_gettop);
        // can register libraries and whatever here
    }

    return nullptr;
}

__attribute__((constructor))
void lib_main() {
    pthread_t ptid;
    pthread_create(&ptid, nullptr, main_thread, nullptr);
}

extern "C" [[gnu::visibility("default")]] [[gnu::used]]
NativeOnModuleLoaded native_init(const NativeAPIEntries *entries) {
    hook_func = entries->hook_func;
    unhook_func = entries->unhook_func;
    return on_library_loaded;
}