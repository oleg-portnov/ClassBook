#pragma once

#include <QObject>

#include "card/LessonFwd.h"
#include "models/AnswersModel.h"

namespace classbook {

class Word;

class CardStore;

class LessonMediator: public QObject
{
    Q_OBJECT

    Q_PROPERTY(AnswersModel* answers_model READ getAnswersModel NOTIFY sigAnswersModelChanged)
    Q_PROPERTY(Word* cur_cord READ getWord NOTIFY sigWordChanged)

public:
    LessonMediator();
    virtual ~LessonMediator();

public:
    void setCardStore(std::shared_ptr<CardStore> card_store);

    AnswersModel* getAnswersModel();
    Word* getWord();

public slots:
    void init();

    void updateWord();

    void userGuessed();
    void userNotGuess();

    void selectLesson(int cur_less_idx);

private:
    void initAnswersModel();

    void loadAllCard();
    void setRandomWord();

    void selectBestAnswers();

    void checkSave();

signals:
    void sigAnswersModelChanged();
    void sigWordChanged();

private:
    const int SAVE_AFTER = 10;
    int m_change_count;

    std::shared_ptr<CardStore> m_card_store;

    AnswersModel* m_ans_model;
    Word* m_cur_word;
}; // LessonMediator

} // ns classbook
