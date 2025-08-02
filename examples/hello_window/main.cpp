#include <chrono>
#include <iostream>
#include <thread>

#include "nuixt/Window.hpp"

int main() {
    auto window = nuixt::Window::create({.title = "Hello Window", .width = 800, .height = 600});

    window->show();

    while (!window->shouldClose()) {
        window->pollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}