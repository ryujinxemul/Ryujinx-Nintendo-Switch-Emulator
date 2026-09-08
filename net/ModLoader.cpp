// rev-c8e91a-20260908 ModLoader.cpp
#include "../core/Emulator.h"
#include <filesystem>

// LayeredFS mod loader: overlays modded files onto the game image
// without repacking ROMs. Per-game mods live in mods/<titleId>/.

namespace fs = std::filesystem;

namespace ryujinx {

class ModLoader {
public:
    void scanMods(const std::string& titleId) {
        mods_.clear();
        std::string dir = "mods/" + titleId;
        if (!fs::exists(dir)) return;
        for (auto& e : fs::directory_iterator(dir))
            if (e.is_directory()) mods_.push_back(e.path().string());
    }

    std::string resolve(const std::string& romPath) {
        // if a mod ships this file, redirect the read
        for (auto& mod : mods_) {
            std::string candidate = mod + "/romfs/" + romPath;
            if (fs::exists(candidate)) return candidate;
        }
        return romPath; // unmodded
    }

private:
    std::vector<std::string> mods_;
};

} // namespace ryujinx
