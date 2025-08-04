#include "core/common/include/ApplicationStyle.h"

#include <QtGlobal> // for Q_OS_WIN, Q_OS_LINUX, Q_OS_ANDROID

#ifdef Q_OS_WIN
#include <core/windows/include/WindowsApplicationStyle.h>
#elif defined(Q_OS_LINUX)
#include <core/windows/include/LinuxApplicationStyle.h>
#elif defined(Q_OS_ANDROID)
#include <core/windows/include/AndroidApplicationStyle.h>
#endif

using namespace core;

std::unique_ptr<ApplicationStyle> ApplicationStyle::Create()
{
#ifdef Q_OS_WIN
    return std::make_unique<WindowsApplicationStyle>();
#elif defined(Q_OS_LINUX)
    return std::make_unique<LinuxApplicationStyle>();
#elif defined(Q_OS_ANDROID)
    return std::make_unique<AndroidApplicationStyle>();
#else
    static_assert(false, "Unsupported platform");
#endif
}
