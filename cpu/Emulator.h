// rev-c8e91a-20260908 Emulator.h
#pragma once
#include <string>

// Ryujinx Emu core types - switch emulation on desktop.

namespace ryujinx {

enum class GpuBackend { Vulkan, OpenGL };

struct ShaderCache { void load(const char* path); };

class GpuRenderer {
public:
    bool init(int w, int h);
    void drawFrame();
    void setScale(int factor);
private:
    bool createVkInstance();
    void pickGpu();
    void createDevice();
    void createSwapchain(int w, int h);
    void* beginFrame();
    void translateTegraCommands(void* cmd);
    void buildPendingPipelines(void* cmd);
    void present(void* cmd);
    ShaderCache shaderCache_;
    bool asyncShaders_ = true;
    int scale_ = 1;
};

struct FirmwareManager {
    bool installFromZip(const std::string& path);
    bool installFromXci(const std::string& path);
    bool validateKeys(const std::string& prodKeys);
};

class Emulator {
public:
    bool loadSystemFiles(const std::string& keys, const std::string& firmwareDir);
    void configureGpu(GpuBackend backend);
    void setResolutionScale(int factor);
    bool bootGame(const std::string& path);
    void run();
    int runGui();
};

} // namespace ryujinx
