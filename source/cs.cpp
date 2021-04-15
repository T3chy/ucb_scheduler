#include "Schedule.h"


// init all cs classes, this could probably be hashmapped or smth too

unordered_map<const char *, Course> init_cs(){
	unordered_map<const char *, Course> csa;
	csa.insert({"cs61a", Course(cs, 61, "a", 4, "") });
	csa.insert({"cs61b", Course(cs, 61, "b", 4, "") });
	csa.insert({"cs162", Course(cs, 162, "", 4, "", {csa["cs61a"]})});
	return csa;
}
