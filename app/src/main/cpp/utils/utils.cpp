//
// Created by Janis on 13.02.2024.
//

#include "utils.h"
#include <array>
#include <cstdint>
#include <cstring>
#include <string>
#include <thread>

#include <iostream>
#include <iomanip>
#include <unwind.h>
#include <dlfcn.h>

namespace utils {
    const std::string random_str(std::size_t length) {
        static const char alphabet[] =
                "abcdefghijklmnopqrstuvwxyz"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "0123456789";

        std::random_device rd;
        std::default_random_engine rng(rd());
        std::uniform_int_distribution<> dist(0, sizeof(alphabet) / sizeof(*alphabet) - 2);

        std::string str;
        str.reserve(length);
        std::generate_n(std::back_inserter(str), length,
                        [&]() { return alphabet[dist(rng)]; });

        return str;
    }

    const std::intptr_t random_int(std::intptr_t min, std::intptr_t max) {
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution <std::intptr_t> distr(min, max);
        return distr(eng);
    };

    const std::string random_bytes(std::size_t length) {
        static const char alphabet[] =
                "ABCDEF"
                "0123456789";

        std::random_device rd;
        std::default_random_engine rng(rd());
        std::uniform_int_distribution<> dist(0, sizeof(alphabet) / sizeof(*alphabet) - 2);

        std::string str;
        str.reserve(length);
        std::generate_n(std::back_inserter(str), length,
                        [&]() { return alphabet[dist(rng)]; });

        return str;
    }

    namespace memory {
        std::uintptr_t find_lib(const char *const library) {
            char filename[0xFF] = {0}, buffer[1024] = {0};

            FILE *fp = nullptr;
            std::uintptr_t address = 0;

            sprintf(filename, "/proc/self/maps");

            fp = fopen(filename, "rt");

            if (fp == nullptr) {
                perror("fopen");
                goto done;
            }

            while (fgets(buffer, sizeof(buffer), fp)) {
                if (strstr(buffer, library)) {
                    address = static_cast<std::uintptr_t>(strtoul(buffer, NULL, 16));
                    goto done;
                }
            }

            done:

            if (fp)
                fclose(fp);

            return address;
        }

        void wait_for_lib(const char *const libname) {
            while (!is_lib_loaded(libname))
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        std::uintptr_t rebase(const char *const libraryName, std::uintptr_t relativeAddr) {
            wait_for_lib(libraryName);
            std::uintptr_t libBase = find_lib(libraryName);

            if (libBase == 0)
                return 0;

            return libBase + relativeAddr;
        }

        bool is_lib_loaded(const char *const libraryName) {
            char line[512] = {0};

            FILE *fp = std::fopen("/proc/self/maps", "rt");

            if (fp != 0) {
                while (std::fgets(line, sizeof(line), fp)) {
                    if (std::strstr(line, libraryName))
                        return true;
                }

                fclose(fp);
            }

            return false;
        }
    }
}