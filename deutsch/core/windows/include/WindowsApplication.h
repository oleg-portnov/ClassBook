#pragma once

#include "core/common/include/Application.h"

namespace core {

class WindowsApplication final : public Application
{
public:
    WindowsApplication(QQmlApplicationEngine& engine);
    ~WindowsApplication() = default;

public:
    void SetGraphicsApi();
    void SetImportPath();
    void LoadMain();
}; // WindowsApplication

} // namespace core
