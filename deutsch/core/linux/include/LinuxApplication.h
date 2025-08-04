#pragma once

#include "core/common/include/Application.h"

namespace core {

class LinuxApplication final : public Application
{
public:
    LinuxApplication(QQmlApplicationEngine& engine);
    ~LinuxApplication() = default;

public:
    void SetGraphicsApi();
    void SetImportPath();
    void LoadMain();
}; // LinuxApplication

} // namespace core
