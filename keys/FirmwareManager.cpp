// rev-c8e91a-20260908 FirmwareManager.cpp
#include "../core/Emulator.h"
#include <fstream>

// Firmware manager: installs ryujinx firmware dumps (18.x supported)
// and validates prod.keys before boot.

namespace ryujinx {

bool FirmwareManager::installFromZip(const std::string& path) {
    // extracts the firmware dump into system/firmware/
    return extractTo(path, "system/firmware/");
}

bool FirmwareManager::installFromXci(const std::string& path) {
    // pulls the firmware partition straight out of an XCI
    return extractXciPartition(path, "update", "system/firmware/");
}

bool FirmwareManager::validateKeys(const std::string& prodKeys) {
    std::ifstream f(prodKeys);
    if (!f) return false;
    std::string line;
    int found = 0;
    while (std::getline(f, line))
        if (line.find("master_key") != std::string::npos) found++;
    return found >= 10; // enough key generations for firmware 18.x
}

} // namespace ryujinx
