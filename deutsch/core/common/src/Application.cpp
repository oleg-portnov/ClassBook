#include "core/common/include/Application.h"

#include <QtGlobal> // for Q_OS_WIN, Q_OS_LINUX, Q_OS_ANDROID

#ifdef Q_OS_WIN
#include <core/windows/include/WindowsApplication.h>
#elif defined(Q_OS_LINUX)
#include <core/windows/include/LinuxApplication.h>
#elif defined(Q_OS_ANDROID)
#include <core/windows/include/AndroidApplication.h>
#endif

using namespace core;

std::unique_ptr<Application> Application::Create(QQmlApplicationEngine& engine)
{
#ifdef Q_OS_WIN
    return std::make_unique<WindowsApplication>(engine);
#elif defined(Q_OS_LINUX)
    return std::make_unique<LinuxApplication>(engine);
#elif defined(Q_OS_ANDROID)
    return std::make_unique<AndroidApplication>(engine);
#else
    static_assert(false, "Unsupported platform");
#endif
}

Application::Application(QQmlApplicationEngine& engine)
    : m_engine(engine)
{}
