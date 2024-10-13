#pragma once

#include "card/Word.h"

namespace classbook {

inline QString toString(const Word::PartOfSpeech& part_of_speech)
{
    switch (part_of_speech)
    {
        case Word::PartOfSpeech::Verbs:         return "Verben";
        case Word::PartOfSpeech::Nomen:         return "Nomen";
        case Word::PartOfSpeech::Adjectives:    return "Adjektive";
        case Word::PartOfSpeech::Adverbs:       return "Adverbien";
        case Word::PartOfSpeech::FunctionWords: return "Funktionswörter";
        case Word::PartOfSpeech::Expressions:   return "Ausdrücke";
        case Word::PartOfSpeech::Abbreviations: return "Abkürzungen";
    }
}

inline Word::PartOfSpeech fromString(const QString& part_of_speech)
{
         if (part_of_speech == "Verben")          return Word::PartOfSpeech::Verbs;
    else if (part_of_speech == "Nomen")           return Word::PartOfSpeech::Nomen;
    else if (part_of_speech == "Adjektive")       return Word::PartOfSpeech::Adjectives;
    else if (part_of_speech == "Adverbien")       return Word::PartOfSpeech::Adverbs;
    else if (part_of_speech == "Funktionswörter") return Word::PartOfSpeech::FunctionWords;
    else if (part_of_speech == "Ausdrücke")       return Word::PartOfSpeech::Expressions;
    else                                          return Word::PartOfSpeech::Abbreviations;
}

} // ns classbook
