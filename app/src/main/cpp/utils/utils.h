//
// Created by Janis on 13.02.2024.
//

#ifndef DRXPOSED_UTILS_H
#define DRXPOSED_UTILS_H
#include <cstdint>
#include <random>
#include <string>
#include <sstream>
#include <jni.h>
#include <android/log.h>
#include <errno.h>
#include <unistd.h>
#include <sys/resource.h>

#define TAG "rex"

#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__))

namespace utils {
    const std::string random_str( std::size_t length );
    const std::string random_bytes( std::size_t length );
    const std::intptr_t random_int(std::intptr_t min, std::intptr_t max);

    namespace memory {
        std::uintptr_t find_lib(const char* const library);
        void wait_for_lib(const char* const libname);
        std::uintptr_t rebase(const char* const libraryName, std::uintptr_t relativeAddr);
        bool is_lib_loaded(const char* const libraryName);
    }
}
#endif //DRXPOSED_UTILS_H
