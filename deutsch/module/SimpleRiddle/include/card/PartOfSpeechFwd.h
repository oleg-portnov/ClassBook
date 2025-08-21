#pragma once

#include <QtQmlIntegration>

namespace simple_riddle::types {

Q_NAMESPACE
QML_ELEMENT

enum class PartOfSpeech {
    Verbs,         // Verben          – Verbs
    Nomen,         // Nomen           – Nouns
    Adjectives,    // Adjektive       – Adjectives
    Adverbs,       // Adverbien       – Adverbs
    FunctionWords, // Funktionswörter – Function words
    Expressions,   // Ausdrücke       – Expressions
    Abbreviations  // Abkürzungen     – Abbreviations
}; // PartOfSpeech

Q_ENUM_NS(PartOfSpeech)

} // ns simple_riddle::types

namespace simple_riddle {

// using namespace types;

inline QString toString(const types::PartOfSpeech& part_of_speech)
{
    switch (part_of_speech)
    {
        case types::PartOfSpeech::Verbs:         return "Verben";
        case types::PartOfSpeech::Nomen:         return "Nomen";
        case types::PartOfSpeech::Adjectives:    return "Adjektive";
        case types::PartOfSpeech::Adverbs:       return "Adverbien";
        case types::PartOfSpeech::FunctionWords: return "Funktionswörter";
        case types::PartOfSpeech::Expressions:   return "Ausdrücke";
        case types::PartOfSpeech::Abbreviations: return "Abkürzungen";
    }

    return "";
}

inline types::PartOfSpeech fromString(const QString& part_of_speech)
{
         if (part_of_speech == "Verben")          return types::PartOfSpeech::Verbs;
    else if (part_of_speech == "Nomen")           return types::PartOfSpeech::Nomen;
    else if (part_of_speech == "Adjektive")       return types::PartOfSpeech::Adjectives;
    else if (part_of_speech == "Adverbien")       return types::PartOfSpeech::Adverbs;
    else if (part_of_speech == "Funktionswörter") return types::PartOfSpeech::FunctionWords;
    else if (part_of_speech == "Ausdrücke")       return types::PartOfSpeech::Expressions;
    else                                          return types::PartOfSpeech::Abbreviations;
}

} // ns simple_riddle
