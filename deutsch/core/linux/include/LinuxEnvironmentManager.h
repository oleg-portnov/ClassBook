#pragma once

#include "core/common/include/EnvironmentManager.h"

namespace core {

class LinuxEnvironmentManager final : public EnvironmentManager {
public:
    void SetEnvironmentVariables() override;
}; // LinuxEnvironmentManager

} // namespace core
