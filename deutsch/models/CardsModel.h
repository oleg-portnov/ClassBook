#pragma once

#include <QtQmlIntegration>
#include <QAbstractListModel>

namespace classbook {

class WordCard;

class CardsModel : public QAbstractListModel
{
    Q_OBJECT

    QML_ELEMENT

public:
    enum class LoadedCardsType {
        None,
        UserCards,
        Lektion
    }; // LoadedCardsType

    enum InfoRoles {
        Id = Qt::UserRole + 1,
        Image,
        TextRu,
        TextDe,
        Showing,
        PartOfSpeech,
        Correctly,
        Incorrect
    }; // InfoRoles

public:
    Q_INVOKABLE int getRandomIndex() const;

    Q_INVOKABLE void setLection(int lek_idx);
    Q_INVOKABLE void saveLection();

    Q_INVOKABLE void loadRandomCards();
    Q_INVOKABLE void loadFromResource(int lek_idx);

    Q_INVOKABLE void saveToFile(const QString& path);
    Q_INVOKABLE bool loadFromFile(const QString& path);

    Q_INVOKABLE QString copyToImgFolder(const QString& source, const QString& destination) const;

    Q_INVOKABLE QString getSourceImg(int row) const;

    Q_INVOKABLE int indexById(int id) const;

    Q_INVOKABLE QString getId(int row) const;

    Q_INVOKABLE QString getTextRu(int row) const;
    Q_INVOKABLE QString getTextDe(int row) const;

    Q_INVOKABLE QString getPartOfSpeech(int row) const;

    Q_INVOKABLE int getShowingCount(int row) const;
    Q_INVOKABLE void increaseShowingCount(int row);

    Q_INVOKABLE int getCorrectlyCount(int row) const;
    Q_INVOKABLE void increaseCorrectlyCount(int row);

    Q_INVOKABLE int getIncorrectCount(int row) const;
    Q_INVOKABLE void increaseIncorrectCount(int row);

public:
    CardsModel(QObject* parent = nullptr);
    virtual ~CardsModel();

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

public slots:
    void addCard(const QJsonObject& card);

private:
    QHash<int, QByteArray> roleNames() const override;

    void reloadLektion(int lek_num);

    QString removeFilePrefix(const QString& path) const;

    QString getFileDataName() const;
    QString getFileLektionName(int lek_num) const;

    QString getImgFolder() const;

    void increaseValue(const QModelIndex& index, int role);

signals:
    void sigCardsChanged();

private:
    QList<WordCard> m_cards;

    LoadedCardsType m_loaded_cards_type;

    int m_lektion_num;
    int m_max_lektion_idx;
}; // NetConnModel

} // ns classbook
