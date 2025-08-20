#include <QtQml/QQmlEngine>
#include <QtQml/QQmlExtensionPlugin>

#include "include/mediators/LessonMediator.h"

class SimpleRiddlePlugin : public QQmlExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override
    {
        Q_ASSERT(uri == QLatin1String("SimpleRiddle"));

        qmlRegisterSingletonType<LessonMediator>(uri, 1, 0, "LessonMediator", [](QQmlEngine *, QJSEngine *) -> QObject * { return new LessonMediator(); });

        // qmlRegisterType<CardStore>(uri, 1, 0, "CardStore");
        // qmlRegisterType<AnswersModel>(uri, 1, 0, "AnswersModel");
        // qmlRegisterType<LessonMediator>(uri, 1, 0, "LessonMediator");
    }
}; // SimpleRiddlePlugin

#include "plugin.moc"

