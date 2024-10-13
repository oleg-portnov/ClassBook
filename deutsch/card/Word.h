#pragma once

#include <QObject>

namespace classbook {

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

    Q_PROPERTY(int views     READ getViews     WRITE setViews     NOTIFY sigViewsChanged)

    Q_PROPERTY(int correct   READ getCorrect   WRITE setCorrect   NOTIFY sigCorrectChanged)
    Q_PROPERTY(int incorrect READ getIncorrect WRITE setIncorrect NOTIFY sigIncorrectChanged)

    Q_PROPERTY(QString de_text READ getDeText WRITE setDeText NOTIFY sigDeTextChanged)
    Q_PROPERTY(QString ru_text READ getRuText WRITE setRuText NOTIFY sigRuTextChanged)

    Q_PROPERTY(QString part_of_speech_text READ getPartOfSpeechText NOTIFY sigPartOfSpeechTextChanged)

    Q_PROPERTY(PartOfSpeech part_of_speech READ getPartOfSpeech WRITE setPartOfSpeech NOTIFY sigPartOfSpeechChanged)

public:
    explicit Word(const QJsonObject& data);
    explicit Word(Word&& other);
    virtual ~Word();

public:
    bool operator!= (const Word& other) const;
    bool operator< (const Word& other) const;

    Word& operator= (const QJsonObject& data);

    Word& operator= (Word&& other);

    Word& operator= (const Word& other) = delete;

public:
    int getDifficulty() const;

public slots:
    int getViews() const;
    void setViews(int new_views);

    int getCorrect() const;
    void setCorrect(int new_value);

    int getIncorrect() const;
    void setIncorrect(int new_value);

    QString getDeText() const;
    void setDeText(const QString& new_de_text);

    QString getRuText() const;
    void setRuText(const QString& new_ru_text);

    QString getPartOfSpeechText() const;

    PartOfSpeech getPartOfSpeech() const;
    void setPartOfSpeech(const PartOfSpeech& new_part_of_speech);

signals:
    void sigViewsChanged();

    void sigCorrectChanged();
    void sigIncorrectChanged();

    void sigDeTextChanged();
    void sigRuTextChanged();

    void sigPartOfSpeechTextChanged();

    void sigPartOfSpeechChanged();

private:
    int m_id;

    int m_views;

    int m_correct;
    int m_incorrect;

    QString m_de_text;
    QString m_ru_text;

    PartOfSpeech m_part_of_speech;
}; // Word

} // ns classbook
