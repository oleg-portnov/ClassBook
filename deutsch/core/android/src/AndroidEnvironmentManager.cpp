#include "core/android/include/AndroidEnvironmentManager.h"

#include "pch.h"

using namespace core;

void AndroidEnvironmentManager::SetEnvironmentVariables()
{
    qputenv("QT_ANDROID_NO_EXIT_CALL", "1");
    qputenv("QT_ANDROID_DISABLE_ACCESSIBILITY", "1");
    qputenv("QT_NO_JAVA_STYLE_ITERATORS", "1");
}
