#include "CardsModel.h"
#include "card/WordCard.h"

#include <QVariantMap>

namespace classbook {

int CardsModel::getRandomIndex() const
{
    return QRandomGenerator::global()->bounded(m_max_lektion_idx);
}

inline int toLektionNum(int lek_idx)
{
    return lek_idx + 1;
}

void CardsModel::setLection(int lek_idx)
{
    m_lektion_num = toLektionNum(lek_idx);

    if (lek_idx < 0 || lek_idx > m_max_lektion_idx)
        loadRandomCards();

    if (!loadFromFile(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" + QString("lektion_%1").arg(m_lektion_num)))
        loadFromResource(lek_idx);
}

void CardsModel::saveLection()
{
    QJsonObject json;

    QJsonArray cards_array;
    int ii = 0;
    for (const WordCard& card: m_cards)
    {
        QJsonObject card_obj;
        card_obj["id"] = ++ii;

        card_obj["img"] = card.img_source;

        card_obj["text_ru"] = card.text_ru;
        card_obj["text_de"] = card.text_de;

        card_obj["showing"] = card.showing;

        card_obj["part"] = card.part_of_speech;

        card_obj["correctly"] = card.correctly;
        card_obj["incorrect"] = card.incorrect;

        cards_array.append(card_obj);
    }

    json["cards"] = cards_array;

    QJsonDocument jdoc(json);

    QSaveFile save_file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" + QString("lektion_%1").arg(m_lektion_num));

    if (save_file.open(QIODevice::WriteOnly))
    {
        save_file.write(jdoc.toJson());

        if (save_file.commit())
            qDebug() << "File saved successfully:" << save_file.fileName();
        else
            qWarning() << "Failed to save file:" << save_file.errorString();
    }
    else
    {
        qWarning() << "Couldn't open save file for writing:" << save_file.errorString();
    }
}

void CardsModel::loadRandomCards()
{
    loadFromResource(getRandomIndex());
}

void CardsModel::loadFromResource(int lek_idx)
{
    m_lektion_num = toLektionNum(lek_idx);
    loadFromFile(QString(":/cards/lektion_%1").arg(m_lektion_num));
}

void CardsModel::saveToFile(const QString& path)
{
    QJsonObject json;

    QJsonArray cards_array;
    int ii = 0;
    for (const WordCard& card: m_cards)
    {
        QJsonObject card_obj;
        card_obj["id"] = ++ii;

        card_obj["img"] = card.img_source;

        card_obj["text_ru"] = card.text_ru;
        card_obj["text_de"] = card.text_de;

        card_obj["showing"] = card.showing;

        card_obj["part"] = card.part_of_speech;

        card_obj["correctly"] = card.correctly;
        card_obj["incorrect"] = card.incorrect;

        cards_array.append(card_obj);
    }

    json["cards"] = cards_array;

    QJsonDocument jdoc(json);

    QString cpp_path = removeFilePrefix(path);

    QDir dir(cpp_path);
    if (!dir.exists())
    {
        qDebug() << "Directory doesn't exist. Creating directory: " << path;

        if (!dir.mkpath("."))
        {
            qWarning() << "Failed to create directory: " << path;
            return;
        }
    }

    QString full_patch = cpp_path + getFileDataName();
    QSaveFile save_file(full_patch);

    if (save_file.open(QIODevice::WriteOnly))
    {
        save_file.write(jdoc.toJson());

        if (save_file.commit())
            qInfo() << "File saved successfully:" << full_patch;
        else
            qWarning() << "Failed to save file:" << save_file.errorString();
    }
    else
    {
        qWarning() << "Couldn't open save file for writing:" << save_file.errorString();
    }
}

bool CardsModel::loadFromFile(const QString& path)
{
    QFile load_file(removeFilePrefix(path));

    if (!load_file.exists())
    {
        qWarning() << "Failed to open file at path:" << path << ". File does not exist";
        return false;
    }

    if (!load_file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open file at path:" << path << "." << load_file.errorString();
        return false;
    }

    QByteArray save_data = load_file.readAll();
    QJsonDocument load_doc(QJsonDocument::fromJson(save_data));

    m_cards.clear();

    QJsonArray cards_array = load_doc["cards"].toArray();

    bool added = false;

    for (const auto& card_value: cards_array)
    {
        addCard(card_value.toObject());
        added = true;
    }

    if (added)
    {
        m_loaded_cards_type = LoadedCardsType::UserCards;
        emit sigCardsChanged();
    }

    return true;
}

QString CardsModel::copyToImgFolder(const QString& source, const QString& destination) const
{
    QFile source_file(removeFilePrefix(source));

    QString dir_destination = removeFilePrefix(destination) + getImgFolder();

    QDir dir(dir_destination);
    if (!dir.exists())
    {
        qDebug() << "Directory doesn't exist. Creating directory: " << dir_destination;

        if (!dir.mkpath("."))
        {
            qWarning() << "Failed to create directory: " << dir_destination;
            return dir_destination;
        }
    }

    const QFileInfo info(source_file);

    QString full_destination = dir_destination + info.fileName();

    if (source_file.copy(full_destination))
        qDebug() << "File copied successfully.";
    else
        qDebug() << "Failed to copy file: " << source_file.errorString();

    return full_destination;
}

QString CardsModel::getSourceImg(int row) const
{
    return QString("file://") + data(index(row), InfoRoles::Image).toString();
}

int CardsModel::indexById(int id) const
{
    return std::distance(m_cards.begin(), std::find_if(m_cards.begin(), m_cards.end(), [id](const WordCard& item){return id == item.id;}));
}

QString CardsModel::getId(int row) const
{
    return data(index(row), InfoRoles::Id).toString();
}

QString CardsModel::getTextRu(int row) const
{
    return data(index(row), InfoRoles::TextRu).toString();
}

QString CardsModel::getTextDe(int row) const
{
    return data(index(row), InfoRoles::TextDe).toString();
}

QString CardsModel::getPartOfSpeech(int row) const
{
    return data(index(row), InfoRoles::PartOfSpeech).toString();
}

int CardsModel::getShowingCount(int row) const
{
    return data(index(row), InfoRoles::Showing).toInt();
}

void CardsModel::increaseShowingCount(int row)
{
    increaseValue(index(row), InfoRoles::Showing);
}

int CardsModel::getCorrectlyCount(int row) const
{
    return data(index(row), InfoRoles::Correctly).toInt();
}

void CardsModel::increaseCorrectlyCount(int row)
{
    increaseValue(index(row), InfoRoles::Correctly);
}

int CardsModel::getIncorrectCount(int row) const
{
    return data(index(row), InfoRoles::Incorrect).toInt();
}

void CardsModel::increaseIncorrectCount(int row)
{
    increaseValue(index(row), InfoRoles::Incorrect);
}

CardsModel::CardsModel(QObject* parent)
    : QAbstractListModel(parent)
    , m_loaded_cards_type(LoadedCardsType::None)
    , m_lektion_num(-1)
    , m_max_lektion_idx(5)
{}

CardsModel::~CardsModel()
{}

int CardsModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_cards.count();
}

QVariant CardsModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_cards.count())
        return QVariant();

    const WordCard& card = m_cards[index.row()];

    if (role == Id)
        return card.id;
    else if (role == Image)
        return card.img_source;
    else if (role == TextRu)
        return card.text_ru;
    else if (role == TextDe)
        return card.text_de;
    else if (role == Showing)
        return card.showing;
    else if (role == PartOfSpeech)
        return card.part_of_speech;
    else if (role == Correctly)
        return card.correctly;
    else if (role == Incorrect)
        return card.incorrect;

    return QVariant();
}

void CardsModel::addCard(const QJsonObject& card)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_cards.append({card.value("id").toInt(),
                    card.value("showing").toInt(),
                    card.value("correctly").toInt(),
                    card.value("incorrect").toInt(),
                    card.value("img_source").toString(),
                    card.value("text_ru").toString(),
                    card.value("text_de").toString(),
                    card.value("part_of_speech").toString()});
    endInsertRows();
}

QHash<int, QByteArray> CardsModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[Id] = "id";
    roles[Image] = "img";
    roles[TextRu] = "text_ru";
    roles[TextDe] = "text_de";
    roles[PartOfSpeech] = "part_of_speech";
    roles[Showing] = "showing";
    roles[Correctly] = "correctly";
    roles[Incorrect] = "incorrect";

    return roles;
}

void CardsModel::reloadLektion(int lek_num)
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    m_cards.clear();
    endRemoveRows();

    QFile load_file(QString(":/cards/lektion_%1").arg(lek_num));

    if (load_file.open(QIODevice::ReadOnly))
    {
        QByteArray save_data = load_file.readAll();
        QJsonDocument load_doc(QJsonDocument::fromJson(save_data));

        QJsonArray cards_array = load_doc["cards"].toArray();

        bool added = false;

        for (const auto& card_value: cards_array)
        {
            addCard(card_value.toObject());
            added = true;
        }

        if (added)
        {
            m_lektion_num = lek_num;
            m_loaded_cards_type = LoadedCardsType::Lektion;
            emit sigCardsChanged();
        }
    }
    else
    {
        qWarning() << "Couldn't open load file";
    }
}

QString CardsModel::removeFilePrefix(const QString& path) const
{
    const QString file_prefix = "file://";
    return path.startsWith(file_prefix) ? path.mid(file_prefix.length())
                                        : path;
}

QString CardsModel::getFileDataName() const
{
    return QString("/cards");
}

QString CardsModel::getFileLektionName(int lek_num) const
{
    return QString("/lektion_%1").arg(lek_num);
}

QString CardsModel::getImgFolder() const
{
    return QString("/img/");
}

void CardsModel::increaseValue(const QModelIndex& index, int role)
{
    if (index.row() < 0 || index.row() >= m_cards.count())
        return;

    WordCard& card = m_cards[index.row()];

    if (role == Showing)
        ++card.showing;
    else if (role == Correctly)
        ++card.correctly;
    else if (role == Incorrect)
        ++card.incorrect;
}

} // ns classbook
