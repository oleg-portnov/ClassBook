#include "mediators/LessonMediator.h"

int main(int argc, char* argv[])
{
#if defined(Q_OS_ANDROID)
    qputenv("QT_ANDROID_NO_EXIT_CALL", "1");
    qputenv("QT_ANDROID_DISABLE_ACCESSIBILITY", "1");
    qputenv("QT_NO_JAVA_STYLE_ITERATORS", "1");
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app,    [](){QCoreApplication::exit(EXIT_FAILURE);},
                     Qt::QueuedConnection);

    classbook::LessonMediator mediator;

    engine.rootContext()->setContextProperty("LesMediator", &mediator);

    engine.load(QUrl("qrc:/component/main.qml"));

    return app.exec();
}
