#pragma once

#include <QAbstractListModel>

#include "card/WordFwd.h"

namespace classbook {

class AnswersModel : public QAbstractListModel
{
    Q_OBJECT

    enum RoleType {
        IsCorrect = Qt::DisplayRole + 1
    }; // Type

    Q_PROPERTY(bool need_tr READ getNeedTr WRITE setNeedTr NOTIFY sigNeedTrChanged)

public:
    explicit AnswersModel(QObject* parent = nullptr);
    virtual ~AnswersModel();

public:
    bool getNeedTr() const;
    void setNeedTr(bool need_tr);

    void setCorrectAnswer(const Word* correct_word);

    void setNewData(const std::vector<const Word*>& new_data);

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

signals:
    void sigNeedTrChanged();

private:
    const Word* m_correct_word;
    std::vector<const Word*> m_ans_words;
    bool m_need_tr;
}; // AnswersModel

} // ns classbook
