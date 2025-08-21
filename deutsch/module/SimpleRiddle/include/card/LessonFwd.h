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
    Less_10
}; // Less

inline int toNumber(const Less& lesson_num)
{
    return static_cast<int>(lesson_num) + 1;
    // return utils::toUType(lesson_num) + 1;
}

inline Less toLesson(int value)
{
    const bool is_valid = value >= toNumber(Less::Null) && value <= toNumber(Less::Less_10);

    return is_valid ? static_cast<Less>(value)
                    : Less::Null;
}

} // ns simple_riddle
