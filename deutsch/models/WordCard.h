#pragma once

#include <QString>

namespace classbook {

struct WordCard
{
    int id;

    int showing;

    int correctly;
    int incorrect;

    QString img_source;

    QString text_ru;
    QString text_de;

    QString part_of_speech;
}; // WordCard

} // ns classbook
