#ifndef NUIXT_INPUT_HPP
#define NUIXT_INPUT_HPP

#include <cinttypes>

namespace nuixt {

enum class KeyModifier : uint8_t {
    eNone = 0,
    eControl = 1 << 0,
    eAlt = 1 << 1,
    eShift = 1 << 2,
    eSuper = 1 << 3,   // cmd on macOS, win on Windows and super on Linux
    ePrimary = 1 << 4  // cmd on macOS, ctrl everywhere else
};

enum class KeyCode : uint16_t {
    eNone,
    eA,
    eB,
    eC,
    eD,
    eF,
    eG,
    eH,
    eI,
    eJ,
    eK,
    eL,
    eM,
    eN,
    eO,
    eP,
    eQ,
    eR,
    eS,
    eT,
    eU,
    eV,
    eW,
    eX,
    eY,
    eZ,
    eF1,
    eF2,
    eF3,
    eF4,
    eF5,
    eF6,
    eF7,
    eF8,
    eF9,
    eF10,
    eF11,
    eF12,
    eEnter,
    eEscape
};

struct Shortcut {
    KeyModifier modifiers = KeyModifier::eNone;
    KeyCode key = KeyCode::eNone;

    constexpr Shortcut() = default;
    constexpr Shortcut(KeyModifier modifiers, KeyCode key) : modifiers(modifiers), key(key) {}
};

}  // namespace nuixt

#endif  // NUIXT_INPUT_HPP