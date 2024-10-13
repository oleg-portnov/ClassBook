#pragma once

#include "card/WordFwd.h"
#include "card/LessonFwd.h"

#include <QString>

namespace classbook {

class CardStore
{
public:
    CardStore();
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

} // ns classbook
