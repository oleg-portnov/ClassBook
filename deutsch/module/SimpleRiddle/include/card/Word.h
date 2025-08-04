#pragma once

#include <QJsonObject>

// namespace classbook {

class Word : public QObject
{
    Q_OBJECT

public:
    enum class PartOfSpeech {
        Verbs,         // Verben          – Verbs
        Nomen,         // Nomen           – Nouns
        Adjectives,    // Adjektive       – Adjectives
        Adverbs,       // Adverbien       – Adverbs
        FunctionWords, // Funktionswörter – Function words
        Expressions,   // Ausdrücke       – Expressions
        Abbreviations  // Abkürzungen     – Abbreviations
    }; // PartOfSpeech

    Q_ENUM(PartOfSpeech)

    Q_PROPERTY(int id MEMBER m_id)

    Q_PROPERTY(int views READ getViews NOTIFY sigViewsChanged)

    Q_PROPERTY(int correct   READ getCorrect   NOTIFY sigCorrectChanged)
    Q_PROPERTY(int incorrect READ getIncorrect NOTIFY sigIncorrectChanged)

    Q_PROPERTY(QString de_text READ getDeText CONSTANT)
    Q_PROPERTY(QString ru_text READ getRuText CONSTANT)

    Q_PROPERTY(QString part_of_speech_text READ getPartOfSpeechText CONSTANT)

    Q_PROPERTY(PartOfSpeech part_of_speech READ getPartOfSpeech CONSTANT)

public:
    explicit Word(const QJsonObject& data);
    explicit Word(Word&& other);
    virtual ~Word();

public:
    Word& operator= (const Word& other) = delete;

public:
    bool operator!= (const Word& other) const;
    bool operator< (const Word& other) const;

    Word& operator= (const QJsonObject& data);

    Word& operator= (Word&& other);

public:
    int getDifficulty() const;

    void show();

    void guessed();
    void notGuess();

public slots:
    int getViews() const;

    int getCorrect() const;

    int getIncorrect() const;

    QString getDeText() const;

    QString getRuText() const;

    QString getPartOfSpeechText() const;

    PartOfSpeech getPartOfSpeech() const;

signals:
    void sigViewsChanged();

    void sigCorrectChanged();
    void sigIncorrectChanged();

private:
    int m_id;

    int m_views;

    int m_correct;
    int m_incorrect;

    QString m_de_text;
    QString m_ru_text;

    PartOfSpeech m_part_of_speech;
}; // Word

// } // ns classbook
