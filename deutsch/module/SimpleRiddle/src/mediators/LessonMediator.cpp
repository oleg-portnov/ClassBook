#include "include/mediators/LessonMediator.h"

#include "include/card/Word.h"
#include "include/models/CardStore.h"

// namespace classbook {

LessonMediator::LessonMediator()
    : m_change_count(0)
    , m_card_store(std::make_unique<CardStore>())
    , m_ans_model(std::make_unique<AnswersModel>())
    , m_cur_word(nullptr)
{
    // qmlRegisterType<classbook::Word>("classbook", 1, 0, "Word");
    // qmlRegisterType<classbook::AnswersModel>("classbook", 1, 0, "AnswersModel");
    // qmlRegisterType<classbook::LessonMediator>("classbook", 1, 0, "LessonMediator");
}

LessonMediator::~LessonMediator()
{}

AnswersModel* LessonMediator::getAnswersModel()
{
    return m_ans_model.get();
}

Word* LessonMediator::getWord()
{
    return m_cur_word;
}

void LessonMediator::init()
{
    loadAllCard();
    setRandomWord();
}

void LessonMediator::updateWord()
{
    ++m_change_count;
    checkSave();

    setRandomWord();
}

void LessonMediator::userGuessed()
{
    m_cur_word->guessed();
}

void LessonMediator::userNotGuess()
{
    m_cur_word->notGuess();
}

void LessonMediator::selectLesson(int cur_less_idx)
{
    m_card_store->setLessNum(static_cast<Less>(cur_less_idx + 1));
}

void LessonMediator::loadAllCard()
{
    if (!m_card_store->loadAllCard())
        qFatal() << "LessonMediator - Unable to load lessons!";
}

void LessonMediator::setRandomWord()
{
    m_cur_word = m_card_store->getNewWord();
    assert(m_cur_word);
    if (!m_cur_word)
        return;
    m_cur_word->show();
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

// } // ns classbook
