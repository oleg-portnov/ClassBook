#pragma once

#include "core/common/include/ApplicationStyle.h"

namespace core {

class WindowsApplicationStyle final : public ApplicationStyle
{
public:
    void ApplyStyle() override;
}; // WindowsApplicationStyle

} // namespace core
