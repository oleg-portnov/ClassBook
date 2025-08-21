#include "include/models/AnswersModel.h"

#include "include/card/Word.h"

#include <QRandomGenerator>

namespace simple_riddle {

AnswersModel::AnswersModel(QObject* parent)
    : QAbstractListModel(parent)
    , m_need_tr(false)
    , m_correct_word(nullptr)
{}

AnswersModel::~AnswersModel()
{}

bool AnswersModel::getNeedTr() const
{
    return m_need_tr;
}

void AnswersModel::setNeedTr(bool need_tr)
{
    m_need_tr = need_tr;
    emit sigNeedTrChanged();
}

void AnswersModel::setCorrectAnswer(p_word correct_word)
{
    assert(correct_word);

    m_correct_word = correct_word;

    emit dataChanged(index(0),
                     index(m_ans_words.size() - 1),
                     { RoleType::IsCorrect });
}

void AnswersModel::setNewData(const words_data& new_data)
{
    beginResetModel();
    m_ans_words.clear();
    endResetModel();

    setNeedTr(QRandomGenerator::global()->bounded(2) == 1);

    beginInsertRows(QModelIndex(), 0, new_data.size() - 1);
    m_ans_words = new_data;
    endInsertRows();
}

int AnswersModel::rowCount(const QModelIndex& parent) const
{
    return m_ans_words.size();
}

QVariant AnswersModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == RoleType::DispText)
    {
        return getNeedTr() ? m_ans_words[index.row()]->getDeText()
                           : m_ans_words[index.row()]->getRuText();
    }
    else if (role == RoleType::IsCorrect)
    {
        return m_correct_word == m_ans_words[index.row()];
    }

    return QVariant();
}

QHash<int, QByteArray> AnswersModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[RoleType::DispText]  = "displayed_text";
    roles[RoleType::IsCorrect] = "is_correct";
    return roles;
}

} // ns simple_riddle
