#include "LessonMediator.h"

#include "card/Word.h"
#include "models/CardStore.h"

#include <QDebug>
#include <QRandomGenerator>

#include <ranges>
#include <algorithm>

namespace classbook {

LessonMediator::LessonMediator()
    : SAVE_AFTER(4)
    , m_change_count(0)
    , m_ans_model(nullptr)
    , m_cur_word(nullptr)
{}

LessonMediator::~LessonMediator()
{}

void LessonMediator::setCardStore(std::shared_ptr<CardStore> card_store)
{
    m_card_store = card_store;
}

AnswersModel* LessonMediator::getAnswersModel()
{
    return m_ans_model;
}

Word* LessonMediator::getWord()
{
    return m_cur_word;
}

void LessonMediator::init()
{
    loadAllCard();
    initAnswersModel();
    setRandomWord();
}

void LessonMediator::updateWord()
{
    setRandomWord();
    ++m_change_count;
    checkSave();
}

void LessonMediator::userGuessed()
{
    m_cur_word->setCorrect(m_cur_word->getCorrect() + 1);   // todo hide
}

void LessonMediator::userNotGuess()
{
    m_cur_word->setIncorrect(m_cur_word->getIncorrect() + 1);   // todo hide
}

void LessonMediator::selectLesson(int cur_less_idx)
{
    m_card_store->setLessNum(static_cast<Less>(cur_less_idx + 1));
}

void LessonMediator::initAnswersModel()
{
    m_ans_model = new AnswersModel;
    emit sigAnswersModelChanged();
}

void LessonMediator::loadAllCard()
{
    if (!m_card_store->loadAllCard())
        qFatal() << "LessonMediator - Unable to load lessons!";
}

void LessonMediator::setRandomWord()
{
    m_cur_word = m_card_store->getNewWord();
    selectBestAnswers();
    emit sigWordChanged();
}

void LessonMediator::selectBestAnswers()
{
    assert(m_cur_word);
    if (!m_cur_word)
        return;

    auto all_same_part_of_speech = m_card_store->getAllLesson()
                                   | std::views::join
                                   | std::views::filter([&](const Word& word){return m_cur_word->getPartOfSpeech() == word.getPartOfSpeech();})
                                   | std::views::transform([](const Word& word){return &word;});

    if (all_same_part_of_speech.empty())
        return;

    std::vector<const Word*> words_ptr(all_same_part_of_speech.begin(), all_same_part_of_speech.end());

    auto* gen = QRandomGenerator::global();
    std::ranges::shuffle(words_ptr, *gen);

    const int num_elements = gen->bounded(MIN_WORD_COUNT, std::min<int>(words_ptr.size(), MAX_WORD_COUNT));

    words_ptr.resize(num_elements);
    words_ptr.emplace_back(m_cur_word);

    std::ranges::shuffle(words_ptr, *gen);

    m_ans_model->setNewData(words_ptr);
    m_ans_model->setCorrectAnswer(m_cur_word);
}

void LessonMediator::checkSave()
{
    if (m_change_count >= SAVE_AFTER)
    {
        m_change_count = 0;
        m_card_store->save();
    }
}

} // ns classbook
