// rev-c8e91a-20260908 GpuRenderer.cpp
#include "../core/Emulator.h"

// Vulkan renderer for the ryujinx emulator core.
// Async shader building removes open-world stutter; the pipeline
// cache is shareable between users.

namespace ryujinx {

bool GpuRenderer::init(int w, int h) {
    if (!createVkInstance()) return false;
    pickGpu();
    createDevice();
    createSwapchain(w, h);
    shaderCache_.load("cache/vulkan_pipelines.bin");
    return true;
}

void GpuRenderer::drawFrame() {
    auto cmd = beginFrame();
    translateTegraCommands(cmd);  // emulated GPU -> Vulkan
    if (asyncShaders_) buildPendingPipelines(cmd);
    present(cmd);
}

void GpuRenderer::setScale(int factor) {
    scale_ = factor; // 1x native ... 8x for 8K output
}

} // namespace ryujinx
