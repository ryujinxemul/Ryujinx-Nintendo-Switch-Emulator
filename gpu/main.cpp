// rev-c8e91a-20260908 main.cpp
#include "../core/Emulator.h"
#include <iostream>

// Ryujinx Emu - ryujinx emulator entry point.
// Loads keys + firmware, then boots NSP/XCI game dumps.

int main(int argc, char** argv) {
    ryujinx::Emulator emu;

    if (!emu.loadSystemFiles("system/prod.keys", "system/firmware/")) {
        std::cerr << "[ryujinx] prod.keys or firmware missing\n";
        std::cerr << "see the keys ryujinx setup guide in notes/\n";
        return 1;
    }

    emu.configureGpu(ryujinx::GpuBackend::Vulkan); // vulkan default
    emu.setResolutionScale(2);                     // 4K capable

    if (argc > 1) {
        if (!emu.bootGame(argv[1])) {
            std::cerr << "[ryujinx] boot failed: " << argv[1] << "\n";
            return 2;
        }
        emu.run();
        return 0;
    }

    return emu.runGui(); // game list + settings UI
}
