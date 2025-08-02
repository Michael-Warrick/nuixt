#ifndef NUIXT_WINDOW_HPP
#define NUIXT_WINDOW_HPP

#include <memory>
#include <string>

namespace nuixt {
class Window {
public:
    struct Properties {
        std::string title = "NUIXT Window";
        int width = 800;
        int height = 600;
    };

    static std::unique_ptr<Window> create(const Properties &properties);
    virtual ~Window() = default;

    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void setTitle(const std::string &title) = 0;
    virtual void pollEvents() = 0;
    virtual bool shouldClose() const = 0;

    virtual void *nativeHandle() const = 0;


protected:
    Window() = default;
};
}  // namespace nuixt

#endif  // NUIXT_WINDOW_HPP