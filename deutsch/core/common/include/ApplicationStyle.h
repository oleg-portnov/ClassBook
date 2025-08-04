#pragma once

#include <memory>

namespace core {

// TODO: create normal name:)
class ApplicationStyle
{
public:
    static std::unique_ptr<ApplicationStyle> Create();

public:
    ApplicationStyle() = default;
    virtual ~ApplicationStyle() = default;

public:
    virtual void ApplyStyle() = 0;
}; // ApplicationStyle

} // namespace core
