#ifndef LIFNEURON_H
#define LIFNEURON_H

#include <vector>
#include <math.h>

#include "global.h"

using namespace std;

class lifneuron
{
public:
    lifneuron();
    ~lifneuron();
    int potential_dynamics(double I);
    int threshold_dynamics();
    int spiking_dynamics(double aTime);
    int I_interpolation(double I, double aTime);
    int run(double I, double aTime);
    int initOutput(string fileName);
    int saveOutput();
    double potential_diff_equation(double I, double y);       // dy/dt = potential_diff_equation(double I, double y)
    int potential_dynamics_RK(double I);

    // variables
    double v;       // membrane potential (mV)
    double vt;      // membrane threshold (mV)
    double time;    // (ms)
    double dt;      // time increment (ms)
    double last_I;  // last value of I received
    vector<double> vect_i;   // interpolated values of I
    vector<double> vect_t;   // interpolated values of time
    vector<double> vect_spike; // spiking times
    ofstream outputStream;    // stream to save t,i,v,vt,spike
    int outputSave;         // 0=do not save, 1=save output to file
    double last_I_RK;

};

#endif // LIFNEURON_H
