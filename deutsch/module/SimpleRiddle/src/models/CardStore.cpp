#include "include/models/CardStore.h"

#include "include/card/Word.h"

#include <QDirIterator>

// namespace classbook {

CardStore::CardStore(QObject* parent)
    : QObject(parent)
    , m_cur_less(Less::Null)
{}

CardStore::~CardStore()
{}

void CardStore::save()
{
    if (m_cur_less == Less::Null)
    {
        m_show_less.sort();
        m_show_less.unique();

        for (int lesson_indx: m_show_less)
            saveLection(getLesson(lesson_indx), toLesson(lesson_indx));

        m_show_less.clear();
    }
    else
    {
        saveLection(getLesson(toNumber(m_cur_less)), m_cur_less);
    }
}

bool CardStore::loadAllCard()
{
    bool loaded = true;

    int lesson_num = static_cast<int>(Less::Less_1);
    int max_lesson_num = static_cast<int>(Less::Less_10);

    for (; lesson_num <= max_lesson_num; ++lesson_num)
    {
        Less lesson = static_cast<Less>(lesson_num);

        loaded = existLessonInFS(lesson) ? loadFromFile(getFilePatchInFS(lesson))
                                         : loadFromFile(getFilePatchInResource(lesson));

        if (!loaded)
            return false;
    }

    return loaded;
}

int CardStore::size() const
{
    return m_lessons.size();
}

void CardStore::setLessNum(Less cur_less)
{
    m_cur_less = cur_less;
}

Word* CardStore::getNewWord()
{
    const bool is_random = m_cur_less == Less::Null;

    const int lessons_indices = m_lessons.size() - 1;
    const int random_idx = is_random ? QRandomGenerator::global()->bounded(lessons_indices)
                                     : static_cast<int>(m_cur_less);
                                     // : utils::toUType(m_cur_less);

    if (is_random)
        m_show_less.emplace_back(random_idx);

    LessonWords* lesson = getLesson(random_idx);

    if (lesson && !lesson->empty())
        return &((*lesson)[QRandomGenerator::global()->bounded(lessons_indices)]);

    return nullptr;
}

const Lessons& CardStore::getAllLesson()
{
    return m_lessons;
}

LessonWords* CardStore::getLesson(int index)
{
    if (index < 0 || index >= static_cast<int>(m_lessons.size()))
        return nullptr;

    return &m_lessons[index];
}

bool CardStore::existLessonInFS(const Less& lesson_num)
{
    return QFile::exists(getFilePatchInFS(lesson_num));
}

bool CardStore::loadFromFile(const QString& path)
{
    QFile load_file(path);

    if (!load_file.exists())
    {
        qWarning() << "Failed to open file at path:" << path << ". " << "File does not exist";
        return false;
    }

    if (!load_file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open file at path:" << path << ". " << load_file.errorString();
        return false;
    }

    const QJsonDocument& load_doc = QJsonDocument::fromJson(load_file.readAll());

    load_file.close();

    const QJsonArray cards_array = load_doc["cards"].toArray();

    LessonWords less_words;
    less_words.reserve(cards_array.size());

    std::transform(cards_array.begin(),
                   cards_array.end(),
                   std::back_inserter(less_words),
                   [](const QJsonValueConstRef& word){return Word(word.toObject());});

    m_lessons.emplace_back(std::move(less_words));

    return true;
}

bool CardStore::saveLection(const LessonWords* lesson, const Less& lesson_num)
{
    QJsonObject json;

    QJsonArray cards_array;
    int ii = 0;
    for (const Word& card: *lesson)
    {
        QJsonObject card_obj;
        card_obj["id"] = ++ii;

        card_obj["text_ru"] = card.getRuText();
        card_obj["text_de"] = card.getDeText();

        card_obj["showing"] = card.getViews();

        card_obj["part"] = card.getPartOfSpeechText();

        card_obj["correctly"] = card.getCorrect();
        card_obj["incorrect"] = card.getIncorrect();

        cards_array.append(card_obj);
    }

    json["cards"] = cards_array;

    QJsonDocument jdoc(json);

    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator();

    QDir dir(path);
    if (!dir.exists())
    {
        if (!dir.mkpath(path))
        {
            qWarning() << "Failed to create directory:" << path;
            return false;
        }
    }

    QSaveFile save_file(path + QString("lektion_%1").arg(static_cast<int>(lesson_num)));

    if (save_file.open(QIODevice::WriteOnly))
    {
        save_file.write(jdoc.toJson());

        if (save_file.commit())
            return true;
        else
            qWarning() << "Failed to save file:" << save_file.errorString();
    }
    else
    {
        qWarning() << "Couldn't open save file for writing:" << save_file.errorString();
    }

    return false;
}

QString CardStore::getFilePatchInFS(const Less& lesson_num)
{
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator() + QString("lektion_%1").arg(toNumber(lesson_num));
}

QString CardStore::getFilePatchInResource(const Less& lesson_num)
{
    return QString(":/SimpleRiddle/imports/SimpleRiddle/resources/cards/lektion_%1").arg(toNumber(lesson_num));
}

// } // ns classbook
