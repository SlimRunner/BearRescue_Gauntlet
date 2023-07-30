#include "BearRescue_Note.hpp"

// Mario life up sound (quarter is 1 at 180 bpm)
const Note sound_intro[7] = {3211266,  12386305, 12582913, 13172737,
                             12910593, 13041665, 13369345};

const Note sound_alarm[8] = {12976132, 4587521, 12976132, 4587524,
                             12976132, 4587521, 12976132, 4587524};

const Note zelda2[62] = {
    3538960,  11599936, 12255248, 12124208, 11665424, 11796496, 11927568,
    11796544, 3538992,  12451856, 12386320, 12255248, 12124192, 11796512,
    11927584, 12058656, 12124208, 12386384, 12451856, 12386320, 11927616,
    3539056,  12124192, 12255248, 12386352, 12582944, 12451872, 12386336,
    12255264, 12386352, 12189728, 12451856, 12386320, 12255264, 12451856,
    12714000, 12845088, 12714000, 12582976, 12451856, 12386320, 12255248,
    12124192, 11796512, 11927584, 12058656, 12124208, 12386384, 12451856,
    12386320, 11927616, 3539056,  12124192, 11862032, 12124208, 12058656,
    12582944, 12255264, 12451872, 12386336, 11796496, 12124224};