#pragma once

#include "include/card/WordFwd.h"
#include "include/card/LessonFwd.h"

#include "list"

#include <QString>

namespace simple_riddle {

class CardStore : public QObject
{
    Q_OBJECT

public:
    explicit CardStore(QObject* parent = nullptr);
    virtual ~CardStore();

public:
    void save();

    bool loadAllCard();

    int size() const;

    void setLessNum(Less cur_less);

    Word* getNewWord();

    const Lessons& getAllLesson();

    LessonWords* getLesson(int index);

private:
    bool existLessonInFS(const Less& lesson_num);

    bool loadFromFile(const QString& path);
    bool saveLection(const LessonWords* lesson, const Less& lesson_num);

    QString getFilePatchInFS(const Less& lesson_num);
    QString getFilePatchInResource(const Less& lesson_num);

private:
    std::list<int> m_show_less;
    Lessons m_lessons;
    Less m_cur_less;
}; // CardStore

} // ns simple_riddle
