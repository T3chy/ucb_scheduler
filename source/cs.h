#include "Schedule.h"
// init all cs classes, this could probably be hashmapped or smth too
struct Course cs61a = Course(cs, 61, "a", 4, "");
struct Course cs162 = Course(cs, 162, "", 4, "", {cs61a});
struct Semester s1 = Semester({cs61a, cs162});
