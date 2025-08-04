#pragma once

#include "include/card/WordFwd.h"

#include <QAbstractListModel>

// namespace classbook {

class AnswersModel : public QAbstractListModel
{
    Q_OBJECT

    enum RoleType {
        IsCorrect = Qt::DisplayRole + 1,
        DispText
    }; // Type

    Q_PROPERTY(bool need_tr READ getNeedTr WRITE setNeedTr NOTIFY sigNeedTrChanged)

    using p_word = const Word*;
    using words_data = std::vector<p_word>;

public:
    explicit AnswersModel(QObject* parent = nullptr);
    virtual ~AnswersModel();

public:
    bool getNeedTr() const;
    void setNeedTr(bool need_tr);

    void setCorrectAnswer(p_word correct_word);

    void setNewData(const words_data& new_data);

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

signals:
    void sigNeedTrChanged();

private:
    bool m_need_tr;
    p_word m_correct_word;
    words_data m_ans_words;
}; // AnswersModel

// } // ns classbook
