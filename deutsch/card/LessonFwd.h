#pragma once

#include "common/utils.h"

namespace classbook {

enum class Less : int {
    Null = -1,
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
    return toUType(lesson_num) + 1;
}

inline Less toLesson(int value)
{
    const bool is_valid = value >= toNumber(Less::Null) && value <= toNumber(Less::Less_10);

    return is_valid ? static_cast<Less>(value)
                    : Less::Null;
}

} // ns classbook
