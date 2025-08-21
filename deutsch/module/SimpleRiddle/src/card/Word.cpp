#include "include/card/Word.h"

#include "include/card/PartOfSpeechFwd.h"

namespace simple_riddle {

Word::Word(const QJsonObject& data)
    : m_id(-1)
    , m_views(data.value("showing").toInt())
    , m_correct(data.value("correctly").toInt())
    , m_incorrect(data.value("incorrect").toInt())
    , m_ru_text(data.value("text_ru").toString())
    , m_de_text(data.value("text_de").toString())
    , m_part_of_speech(fromString(data.value("part_of_speech").toString()))
{}

Word::Word(Word&& other)
    : QObject(other.parent())
    , m_id(other.m_id)
    , m_views(other.m_views)
    , m_correct(other.m_correct)
    , m_incorrect(other.m_incorrect)
    , m_de_text(std::move(other.m_de_text))
    , m_ru_text(std::move(other.m_ru_text))
    , m_part_of_speech(other.m_part_of_speech)
{}

Word::~Word()
{}

bool Word::operator!= (const Word& other) const
{
    return m_de_text != other.m_de_text &&
           m_ru_text != other.m_ru_text;
}

bool Word::operator< (const Word& other) const
{
    return getDifficulty() < other.getDifficulty();
}

Word& Word::operator= (const QJsonObject& data)
{
    m_id = data.value("id").toInt();

    m_views = data.value("showing").toInt();

    m_correct = data.value("correctly").toInt();
    m_incorrect = data.value("incorrect").toInt();

    m_ru_text = data.value("text_ru").toString();
    m_de_text = data.value("text_de").toString();

    m_part_of_speech = fromString(data.value("part_of_speech").toString());

    return *this;
}

Word& Word::operator= (Word&& other)
{
    if (this != &other)
    {
        m_id = other.m_id;

        m_views = other.m_views;

        m_correct   = other.m_correct;
        m_incorrect = other.m_incorrect;

        m_de_text = other.m_de_text;
        m_ru_text = other.m_ru_text;

        m_part_of_speech = other.m_part_of_speech;
    }

    return *this;
}

int Word::getDifficulty() const
{
    if (!m_correct)
        return m_views * m_incorrect;

    return std::ceil(m_views / m_correct) * m_incorrect;
}

void Word::show()
{
    ++m_views;
    emit sigViewsChanged();
}

void Word::guessed()
{
    ++m_correct;
    emit sigCorrectChanged();
}

void Word::notGuess()
{
    ++m_incorrect;
    emit sigIncorrectChanged();
}

int Word::getViews() const
{
    return m_views;
}

int Word::getCorrect() const
{
    return m_correct;
}

int Word::getIncorrect() const
{
    return m_incorrect;
}

QString Word::getDeText() const
{
    return m_de_text;
}

QString Word::getRuText() const
{
    return m_ru_text;
}

QString Word::getPartOfSpeechText() const
{
    return toString(getPartOfSpeech());
}

types::PartOfSpeech Word::getPartOfSpeech() const
{
    return m_part_of_speech;
}

} // ns simple_riddle
