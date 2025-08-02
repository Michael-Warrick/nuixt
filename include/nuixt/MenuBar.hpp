#ifndef NUIXT_MENUBAR_HPP
#define NUIXT_MENUBAR_HPP

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "Input.hpp"

namespace nuixt {

struct MenuItem {
    enum class State { eDisabled = 0, eEnabled = 1 };

    std::string label;
    Shortcut shortcut;
    State state = State::eEnabled;
    std::function<void()> callbackFunction;
    std::vector<MenuItem> items;
    bool isSeparator = false;
};

struct Menu {
    std::string label;
    std::vector<MenuItem> items;
};

class MenuBar {
public:
    MenuBar() = default;
    MenuBar(const std::vector<Menu> &menus) {
        m_menus.resize(menus.size());
        m_menus = menus;
    }
    ~MenuBar() = default;

    void addMenu(const Menu &menu) { m_menus.push_back(menu); }

private:
    std::vector<Menu> m_menus;
};

}  // namespace nuixt

#endif  // NUIXT_MENUBAR_HPP