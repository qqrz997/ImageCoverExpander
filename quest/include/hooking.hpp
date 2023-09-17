#pragma once
#include "main.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

class Hooks {
private:
    inline static std::vector<void (*)(Logger &logger)> installFuncs;
public:
    static void AddInstallFunc(void (*installFunc)(Logger &logger)) {
        installFuncs.push_back(installFunc);
    }

    static void InstallHooks(Logger &logger) {
        for (auto installFunc : installFuncs) {
            installFunc(logger);
        }
    }
};

#define RegisterInstallFunction(func) \
struct __RumbleModRegister##func { \
    __RumbleModRegister##func() { \
        Hooks::AddInstallFunc(func); \
    } \
}; \
static __RumbleModRegister##func __RumbleModRegisterInstance##func;