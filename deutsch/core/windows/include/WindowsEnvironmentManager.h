#pragma once

#include "core/common/include/EnvironmentManager.h"

namespace core {

class WindowsEnvironmentManager final : public EnvironmentManager {
public:
    void SetEnvironmentVariables() override;
}; // WindowsEnvironmentManager

} // namespace core
