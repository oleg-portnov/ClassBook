#pragma once

#include <QString>

namespace classbook {

struct WordCard
{
    int id;

    int showing_count;

    int correctly_count;
    int incorrect_count;

    QString img_source;

    QString text_ru;
    QString text_de;

    QString part_of_speech;
}; // WordCard

} // ns classbook
