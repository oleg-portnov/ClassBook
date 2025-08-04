#pragma once

#include "core/common/include/Application.h"

namespace core {

class AndroidApplication final : public Application
{
public:
    AndroidApplication(QQmlApplicationEngine& engine);
    ~AndroidApplication() = default;

public:
    void SetGraphicsApi();
    void SetImportPath();
    void LoadMain();
}; // AndroidApplication

} // namespace core
