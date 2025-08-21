#pragma once

#include "Word.h"

#include <vector>

namespace simple_riddle {

class Word;

using LessonWords = std::vector<Word>;
using Lessons = std::vector<LessonWords>;

} // ns simple_riddle
