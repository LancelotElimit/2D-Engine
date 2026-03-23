#include "Engine.h"
#include <iostream>

Engine::Engine() : running(false) {}

bool Engine::init() {
    if (!windowManager.init("SDL3 Window Control Demo", 800, 600)) {
        return false;
    }

    if (!renderer2D.init(windowManager.getWindow())) {
        return false;
    }

    if (!resourceManager.loadTexture("test.png", renderer2D.getRenderer())) {
        return false;
    }

    running = true;
    return true;
}

void Engine::run() {
    while (running) {
        inputManager.processEvents(windowManager);

        if (inputManager.shouldQuit()) {
            running = false;
        }

        renderer2D.clear();
        renderer2D.drawTexture(resourceManager.getTexture());
        renderer2D.present();
    }
}

void Engine::shutdown() {
    resourceManager.destroy();
    renderer2D.destroy();
    windowManager.destroy();
}