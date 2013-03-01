#ifndef SENSOR_IIT_H
#define SENSOR_IIT_H

#include <stdlib.h>
#include <iostream>
#include <math.h>

#include "global.h"

using namespace std;

class sensor_iit
{
public:
    sensor_iit();
    sensor_iit(double ax, double ay, double az);
    void init_sensor(double ax, double ay, double az);
    double get_WN(double boundry); // returns a white noise float value within [-boundy:boundry]
    double get_GN(double amean, double astd); // returns a gaussian (parameters: mean & std) noise float value
    double get_2drsp(double sti_x,double sti_y);
    double get_3drsp(double sti_x,double sti_y,double sti_z);
    void set_2dpos(double new_x, double new_y);
    void set_3dpos(double new_x, double new_y, double new_z);
    void move_2dpos(double dx, double dy);

    double x;   // x position coordinates (mm)
    double y;   // y position coordinates (mm)
    double z;   // z position coordinates (mm)

    double pi;      // 3.14 etc ...
};

#endif // SENSOR_IIT_H
