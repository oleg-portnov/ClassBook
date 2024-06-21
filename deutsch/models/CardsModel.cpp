#include "CardsModel.h"
#include "WordCard.h"

#include <QVariantMap>

namespace classbook {

int CardsModel::getRandomIndex() const
{
    return QRandomGenerator::global()->bounded(6/*m_cards.size()*/);
}

void CardsModel::setLection(int lek_num)
{
    if (lek_num >= 0)
    {
        loadFromFile(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" + QString("lektion_%1").arg(lek_num));
    }
    else
    {
        m_lektion_num = 1 + getRandomIndex();
        reloadLektion(m_lektion_num);
    }
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

        card_obj["showing"] = card.showing_count;

        card_obj["part"] = card.part_of_speech;

        card_obj["correctly"] = card.correctly_count;
        card_obj["incorrect"] = card.incorrect_count;

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
    m_lektion_num = getRandomIndex();
    loadFromFile(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" + QString("lektion_%1").arg(m_lektion_num));
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

        card_obj["showing"] = card.showing_count;

        card_obj["part"] = card.part_of_speech;

        card_obj["correctly"] = card.correctly_count;
        card_obj["incorrect"] = card.incorrect_count;

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

void CardsModel::loadFromFile(const QString& path)
{
    QFile load_file(removeFilePrefix(path));

    if (load_file.open(QIODevice::ReadOnly))
    {
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
    }
    else
    {
        qWarning() << "Couldn't open load file:" << load_file.fileName();

        m_lektion_num = 1 + getRandomIndex();
        reloadLektion(m_lektion_num);
    }
}

QString CardsModel::copyToImgFolder(const QString& source, const QString& destination) const
{
    QFile source_file(removeFilePrefix(source));

    QString full_destination;

    QString dir_destination = removeFilePrefix(destination) + getImgFolder();

    QDir dir(dir_destination);
    if (!dir.exists())
    {
        qDebug() << "Directory doesn't exist. Creating directory: " << dir_destination;

        if (!dir.mkpath("."))
        {
            qWarning() << "Failed to create directory: " << dir_destination;
            return full_destination;
        }
    }

    const QFileInfo info(source_file);

    full_destination = dir_destination + info.fileName();

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
    return data(index(row), InfoRoles::ShowingCount).toInt();
}

void CardsModel::increaseShowingCount(int row)
{
    increaseValue(index(row), InfoRoles::ShowingCount);
}

int CardsModel::getCorrectlyCount(int row) const
{
    return data(index(row), InfoRoles::CorrectlyCount).toInt();
}

void CardsModel::increaseCorrectlyCount(int row)
{
    increaseValue(index(row), InfoRoles::CorrectlyCount);
}

int CardsModel::getIncorrectCount(int row) const
{
    return data(index(row), InfoRoles::IncorrectCount).toInt();
}

void CardsModel::increaseIncorrectCount(int row)
{
    increaseValue(index(row), InfoRoles::IncorrectCount);
}

CardsModel::CardsModel(QObject* parent)
    : QAbstractListModel(parent)
    , m_loaded_cards_type(LoadedCardsType::None)
    , m_lektion_num(-1)
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
    else if (role == ShowingCount)
        return card.showing_count;
    else if (role == PartOfSpeech)
        return card.part_of_speech;
    else if (role == CorrectlyCount)
        return card.correctly_count;
    else if (role == IncorrectCount)
        return card.incorrect_count;

    return QVariant();
}

void CardsModel::addCard(const QJsonObject& card)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_cards.append({card.value("id").toInt(),
                    card.value("showing_count").toInt(),
                    card.value("correctly_count").toInt(),
                    card.value("incorrect_count").toInt(),
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
    roles[ShowingCount] = "showing_count";
    roles[CorrectlyCount] = "correctly_count";
    roles[IncorrectCount] = "incorrect_count";

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

    if (role == ShowingCount)
        ++card.showing_count;
    else if (role == CorrectlyCount)
        ++card.correctly_count;
    else if (role == IncorrectCount)
        ++card.incorrect_count;
}

} // ns classbook
