#ifndef LIFNETWORK_H
#define LIFNETWORK_H

#include "global.h"
#include "lifneuron.h"
#include "network_co.h"

class lifnetwork
{
public:
    lifnetwork();
    ~lifnetwork();
    int initLifDynamicsOutput(string fileName);
    int initLifSpikeOutput(string fileName);
    int saveLifSpikeOutput();
    int run(double atime,double * sensor_array);

    double time;
    int nb_mr;
    lifneuron * lifarray;
    network_co net_mc2mr;
    ofstream outputSpikeStream;    // stream to save spike output
    int outputSpikeSave;         // 0=do not save, 1=save output to file
    int outputDynamicsSave;         // 0=do not save, 1=save output to file
};

#endif // LIFNETWORK_H
