#include "gridline.h"


GridLine::GridLine(int start_x, int start_y, int end_x, int end_y)
{
    bresenhamLine(start_x, start_y, end_x, end_y);
}


void GridLine::bresenhamLine(int start_x, int start_y, int end_x, int end_y)
{
    line_xs_.clear();
    line_ys_.clear();
    int dx, dy, incr1, incr2, d, x, y, xend, yend, xdirflag, ydirflag;
    int cnt = 0;

    dx = abs(end_x - start_x);
    dy = abs(end_y - start_y);

    if (dy <= dx)
    {
        d = 2 * dy - dx;
        incr1 = 2 * dy;
        incr2 = 2 * (dy - dx);
        if (start_x > end_x)
        {
            x = end_x;
            y = end_y;
            ydirflag = (-1);
            xend = start_x;
        }
        else
        {
            x = start_x;
            y = start_y;
            ydirflag = 1;
            xend = end_x;
        }
        line_xs_.push_back(x);
        line_ys_.push_back(y);
        cnt++;
        if (((end_y - start_y) * ydirflag) > 0)
        {
            while (x < xend)
            {
              x++;
              if (d < 0)
              {
                d += incr1;
              }
              else
              {
                y++;
                d += incr2;
              }
              line_xs_.push_back(x);
              line_ys_.push_back(y);
              cnt++;
            }
        }
        else
        {
            while (x < xend)
            {
              x++;
              if (d < 0)
              {
                d += incr1;
              }
              else
              {
                y--;
                d += incr2;
              }
              line_xs_.push_back(x);
              line_ys_.push_back(y);
              cnt++;
            }
        }
    }
    else
    {
        d = 2 * dx - dy;
        incr1 = 2 * dx;
        incr2 = 2 * (dx - dy);
        if (start_y > end_y)
        {
            y = end_y;
            x = end_x;
            yend = start_y;
            xdirflag = (-1);
        }
        else
        {
            y = start_y;
            x = start_x;
            yend = end_y;
            xdirflag = 1;
        }
        line_xs_.push_back(x);
        line_ys_.push_back(y);
        cnt++;
        if (((end_x - start_x) * xdirflag) > 0)
        {
            while (y < yend)
            {
              y++;
              if (d < 0)
              {
                d += incr1;
              }
              else
              {
                x++;
                d += incr2;
              }
              line_xs_.push_back(x);
              line_ys_.push_back(y);
              cnt++;
            }
        }
        else
        {
            while (y < yend)
            {
                y++;
                if (d < 0)
                {
                    d += incr1;
                }
                else
                {
                    x--;
                    d += incr2;
                }
                line_xs_.push_back(x);
                line_ys_.push_back(y);
                cnt++;
            }
        }
    }
}
