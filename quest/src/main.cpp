#include "main.hpp"
#include "hooking.hpp"
#include "logging.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"

extern "C" [[maybe_unused]] void setup(ModInfo& info) {
    info = modInfo;
}

extern "C" [[maybe_unused]] void load() {
    il2cpp_functions::Init();
    Hooks::InstallHooks(getLogger());
}