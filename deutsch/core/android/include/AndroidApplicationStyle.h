#pragma once

#include "core/common/include/ApplicationStyle.h"

namespace core {

class AndroidApplicationStyle final : public ApplicationStyle
{
public:
    void ApplyStyle() override;
}; // AndroidApplicationStyle

} // namespace core
