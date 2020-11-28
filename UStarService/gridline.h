#ifndef GRIDLINE_H
#define GRIDLINE_H
#include <vector>
#include <stdlib.h>
class GridLine
{
public:
    GridLine(int start_x, int start_y, int end_x, int end_y);
    void bresenhamLine(int start_x, int start_y, int end_x, int end_y);


    std::vector<int> line_xs_;
    std::vector<int> line_ys_;
};






#endif // GRIDLINE_H

