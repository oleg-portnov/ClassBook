#pragma once

#include <memory>

class QQmlApplicationEngine;

namespace core {

class Application
{
public:
    static std::unique_ptr<Application> Create(QQmlApplicationEngine& engine);

public:
    virtual ~Application() = default;

public:
    virtual void SetGraphicsApi() = 0;  // TODO: make check support backend rhi
    virtual void SetImportPath() = 0;
    virtual void LoadMain() = 0;

protected:
    Application(QQmlApplicationEngine& engine);

protected:
    QQmlApplicationEngine& m_engine;
}; // Application

} // namespace core
