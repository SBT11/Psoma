#ifndef FINGERTIP_H
#define FINGERTIP_H

#include <sstream>
#include <string>
#include <fstream>

#include "sensor_iit.h"
#include "global.h"
#include "network_co.h"

using namespace std;

class fingertip
{
public:
    fingertip();
    ~fingertip();
    void set_2dpos(double new_x, double new_y);
    void set_3dpos(double new_x, double new_y, double new_z);
    void move_2dpos(double dx, double dy);
    int initOutput(string fileName);
    int saveOutput();
    int run(double atime);

    sensor_iit * sensors;
    int nb_sensors;
    double time; //ms
    double x;   // x position (mm)
    double y;   // mm
    double z;   // mm
    network_co layout;  // sensor layout array
    double* sensorRsp;   // array with responses of sensors at time
    ofstream outputStream;    // stream to save t , sensor rsps
    int outputSave;         // 0=do not save, 1=save output to file

};

#endif // FINGERTIP_H
