#include "core/android/include/AndroidApplication.h"

#include "pch.h"

using namespace core;

AndroidApplication::AndroidApplication(QQmlApplicationEngine& engine)
    : Application(engine)
{}

void AndroidApplication::SetGraphicsApi()
{
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);
}

void AndroidApplication::SetImportPath()
{
    m_engine.addImportPath(":/StartModule/imports");
}

void AndroidApplication::LoadMain()
{
    m_engine.load("qrc:/StartModule/imports/StartModule/main.qml");
}
