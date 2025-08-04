#include "pch.h"

#include "core/common/include/EnvironmentManager.h"
#include "core/common/include/Application.h"
#include "core/common/include/ApplicationStyle.h"

int main(int argc, char* argv[])
{
    auto envManager = core::EnvironmentManager::Create();
    envManager->SetEnvironmentVariables();

    QGuiApplication app(argc, argv);

    auto appStyle = core::ApplicationStyle::Create();
    appStyle->ApplyStyle();

    QQmlApplicationEngine engine;

    auto application = core::Application::Create(engine);
    application->SetGraphicsApi();

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app,    [](){QCoreApplication::exit(EXIT_FAILURE);},
                     Qt::QueuedConnection);

    application->SetImportPath();

    application->LoadMain();

    return app.exec();
}
