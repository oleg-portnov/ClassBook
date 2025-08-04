#pragma once

#include "core/common/include/EnvironmentManager.h"

namespace core {

class AndroidEnvironmentManager final : public EnvironmentManager {
public:
    void SetEnvironmentVariables() override;
}; // AndroidEnvironmentManager

} // namespace core
