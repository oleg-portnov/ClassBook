#pragma once

#include "include/models/AnswersModel.h"

#include <QtQmlIntegration>

namespace simple_riddle {

class Word;
class CardStore;

class LessonMediator: public QObject
{
    Q_OBJECT

    QML_ELEMENT

    Q_PROPERTY(AnswersModel* answers_model READ getAnswersModel NOTIFY sigAnswersModelChanged /*REQUIRED*/)
    Q_PROPERTY(Word* cur_cord READ getWord NOTIFY sigWordChanged)

public:
    LessonMediator();
    virtual ~LessonMediator();

public:
    AnswersModel* getAnswersModel();
    Word* getWord();

public slots:
    void init();

    void updateWord();

    void userGuessed();
    void userNotGuess();

    void selectLesson(int cur_less_idx);

private:
    void loadAllCard();
    void setRandomWord();

    void selectBestAnswers();

    void checkSave();

signals:
    void sigAnswersModelChanged();
    void sigWordChanged();

private:
    const int SAVE_AFTER = 10;

    const int MIN_WORD_COUNT = 4;
    const int MAX_WORD_COUNT = 8;

private:
    int m_change_count;

    std::unique_ptr<CardStore> m_card_store;
    std::unique_ptr<AnswersModel> m_ans_model;

    Word* m_cur_word;
}; // LessonMediator

} // ns simple_riddle
