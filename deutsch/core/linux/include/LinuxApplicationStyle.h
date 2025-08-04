#pragma once

#include "core/common/include/ApplicationStyle.h"

namespace core {

class LinuxApplicationStyle final : public ApplicationStyle
{
public:
    LinuxApplicationStyle();
    ~LinuxApplicationStyle();

public:
    void ApplyStyle() override;
}; // LinuxApplicationStyle

} // namespace core
