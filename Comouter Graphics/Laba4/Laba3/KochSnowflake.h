
#ifndef GRAPHICS4_KOCHSNOWFLAKE_H
#define GRAPHICS4_KOCHSNOWFLAKE_H

#include "Line.h"
#include <list>

class KochSnowflake {

public:
    KochSnowflake(){};
    Line* getFirstLine(Line* line);
    Line* getSecondLine(Line* line);
    Line* getThirdLine(Line* line);
    Line* getFourthLine(Line* line);
    void kochFractal(std::list<Line*> &lines);

};


#endif //GRAPHICS4_KOCHSNOWFLAKE_H
