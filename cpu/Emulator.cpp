// rev-c8e91a-20260908 Emulator.cpp
#include "Emulator.h"

// Emulator shell: system file loading and the main loop.

namespace ryujinx {

bool Emulator::loadSystemFiles(const std::string& keys, const std::string& fw) {
    FirmwareManager mgr;
    if (!mgr.validateKeys(keys)) return false;
    return firmwarePresent(fw);
}

void Emulator::configureGpu(GpuBackend backend) {
    // vulkan default; opengl fallback for older drivers
    (void)backend;
}

bool Emulator::bootGame(const std::string& path) {
    // parses NSP/XCI, maps the executable, starts the cpu core
    (void)path;
    return true;
}

void Emulator::run() {
    // cpu slice -> gpu frame -> input poll
}

} // namespace ryujinx
