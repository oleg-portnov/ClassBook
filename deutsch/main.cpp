#include "models/CardsModel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>

int main(int argc, char* argv[])
{
    // https://bugreports.qt.io/browse/QTBUG-82617
    qputenv("QT_ANDROID_NO_EXIT_CALL", "1");

    qputenv("QT_ANDROID_DISABLE_ACCESSIBILITY", "1");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);

    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setSamples(4);
    QSurfaceFormat::setDefaultFormat(format);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app,    [](){ QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);

    qmlRegisterType<classbook::CardsModel>("classbook", 1, 0, "CardsModel");

    if (QThread* thrd = QThread::currentThread())
        thrd->setObjectName("main_thread");

    engine.load(QUrl("qrc:/component/main.qml"));

    return app.exec();
}
