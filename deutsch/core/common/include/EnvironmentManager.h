#pragma once

#include <memory>

namespace core {

class EnvironmentManager {
public:
    static std::unique_ptr<EnvironmentManager> Create();

public:
    EnvironmentManager() = default;
    virtual ~EnvironmentManager() = default;

public:
    virtual void SetEnvironmentVariables() = 0;
}; // EnvironmentManager

} // namespace core
