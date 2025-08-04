#include "core/android/include/AndroidApplicationStyle.h"

#include "pch.h"

using namespace core;

void AndroidApplicationStyle::ApplyStyle()
{
    QQuickStyle::setStyle("Material");
}
