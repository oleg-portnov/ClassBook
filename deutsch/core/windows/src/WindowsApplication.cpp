#include "core/windows/include/WindowsApplication.h"

#include "pch.h"

using namespace core;

WindowsApplication::WindowsApplication(QQmlApplicationEngine& engine)
    : Application(engine)
{}

void WindowsApplication::SetGraphicsApi()
{
    QQuickWindow::setGraphicsApi(QSGRendererInterface::Direct3D11);
}

void WindowsApplication::SetImportPath()
{
    m_engine.addImportPath(":/CoreModule/imports");
    m_engine.addImportPath(":/SimpleRiddle/imports");
}

void WindowsApplication::LoadMain()
{
    m_engine.load("qrc:/CoreModule/imports/CoreModule/core/common/components/main.qml");
}
