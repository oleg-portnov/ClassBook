#pragma once

namespace classbook {

template <typename T>
constexpr auto toUType(T e) noexcept {
    return static_cast<std::underlying_type_t<T>>(e);
}

} // ns classbook
