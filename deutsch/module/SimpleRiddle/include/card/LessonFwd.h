#pragma once

// #include "include/utils.hpp"

namespace simple_riddle {

enum class LessonNumber : int {
    Auto = -1,
    // A1
    Less_1,
    Less_2,
    Less_3,
    Less_4,
    Less_5,
    Less_6,
    Less_7,
    Less_8,
    Less_9,
    Less_10,
    // A2
    Less_11,
    Less_12,
    Less_13,
    Less_14,
    Less_15,
    Less_16,
    Less_17,
    Less_18,
    Less_19,
    Less_20,
    // B1
    Less_21,
    Less_22,
    Less_23,
    Less_24,
    Less_25,
    Less_26,
    Less_27,
    Less_28,
    Less_29,
    Less_30,
}; // Less

inline int toNumber(const LessonNumber& lesson_num)
{
    return static_cast<int>(lesson_num) + 1;
    // return utils::toUType(lesson_num) + 1;
}

inline LessonNumber toLesson(int lesson_num)
{
    const bool isValid = lesson_num >= toNumber(LessonNumber::Auto) &&
                         lesson_num <= toNumber(LessonNumber::Less_10);

    return isValid ? static_cast<LessonNumber>(lesson_num)
                   : LessonNumber::Auto;
}

} // ns simple_riddle
