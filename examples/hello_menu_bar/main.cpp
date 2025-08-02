#include <chrono>
#include <iostream>
#include <thread>

#include "nuixt/MenuBar.hpp"
#include "nuixt/Window.hpp"

int main() {
    auto window = nuixt::Window::create({.title = "Hello Menu Bar", .width = 800, .height = 600});

    nuixt::MenuBar menuBar = nuixt::MenuBar({{.label = "File",
                                              .items = {{.label = "New Document",
                                                         .shortcut = {},
                                                         .state = nuixt::MenuItem::State::eEnabled,
                                                         .callbackFunction = {},
                                                         .items = {},
                                                         .isSeparator = false},

                                                        {.label = "Open Document",
                                                         .shortcut = {},
                                                         .state = nuixt::MenuItem::State::eEnabled,
                                                         .callbackFunction = {},
                                                         .items = {},
                                                         .isSeparator = true},

                                                        {.label = "Save Document",
                                                         .shortcut = {},
                                                         .state = nuixt::MenuItem::State::eEnabled,
                                                         .callbackFunction = {},
                                                         .items = {},
                                                         .isSeparator = false}}}});

    window->show();

    while (!window->shouldClose()) {
        window->pollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}