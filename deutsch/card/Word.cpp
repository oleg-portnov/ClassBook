#include "Word.h"

#include <QJsonObject>

#include "PartOfSpeechFwd.h"

namespace classbook {

Word::Word(const QJsonObject& data)
    : m_id(-1)
    , m_views(data.value("showing").toInt())
    , m_correct(data.value("correctly").toInt())
    , m_incorrect(data.value("incorrect").toInt())
    , m_ru_text(data.value("text_ru").toString())
    , m_de_text(data.value("text_de").toString())
    , m_part_of_speech(fromString(data.value("part_of_speech").toString()))
{}

Word::Word(Word &&other)
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

int Word::getViews() const
{
    return m_views;
}

void Word::setViews(int new_views)
{
    m_views = new_views;
    emit sigViewsChanged();
}

int Word::getCorrect() const
{
    return m_correct;
}

void Word::setCorrect(int new_value)
{
    m_correct = new_value;
    emit sigCorrectChanged();
}

int Word::getIncorrect() const
{
    return m_incorrect;
}

void Word::setIncorrect(int new_value)
{
    m_incorrect = new_value;
    emit sigIncorrectChanged();
}

QString Word::getDeText() const
{
    return m_de_text;
}

void Word::setDeText(const QString& new_de_text)
{
    m_de_text = new_de_text;
    emit sigDeTextChanged();
}

QString Word::getRuText() const
{
    return m_ru_text;
}

void Word::setRuText(const QString& new_ru_text)
{
    m_ru_text = new_ru_text;
    emit sigRuTextChanged();
}

QString Word::getPartOfSpeechText() const
{
    return toString(getPartOfSpeech());
}

Word::PartOfSpeech Word::getPartOfSpeech() const
{
    return m_part_of_speech;
}

void Word::setPartOfSpeech(const PartOfSpeech& new_part_of_speech)
{
    m_part_of_speech = new_part_of_speech;
    emit sigPartOfSpeechChanged();
}

} // ns classbook
