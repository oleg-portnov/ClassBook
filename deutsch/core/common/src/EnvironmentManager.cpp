#include "core/common/include/EnvironmentManager.h"

#include <QtGlobal> // for Q_OS_WIN, Q_OS_LINUX, Q_OS_ANDROID

#ifdef Q_OS_WIN
#include <core/windows/include/WindowsEnvironmentManager.h>
#elif defined(Q_OS_LINUX)
#include <core/windows/include/LinuxEnvironmentManager.h>
#elif defined(Q_OS_ANDROID)
#include <core/windows/include/AndroidEnvironmentManager.h>
#endif

using namespace core;

std::unique_ptr<EnvironmentManager> EnvironmentManager::Create()
{
#ifdef Q_OS_WIN
    return std::make_unique<WindowsEnvironmentManager>();
#elif defined(Q_OS_LINUX)
    return std::make_unique<LinuxEnvironmentManager>(engine);
#elif defined(Q_OS_ANDROID)
    return std::make_unique<AndroidEnvironmentManager>(engine);
#else
    static_assert(false, "Unsupported platform");
#endif
}
