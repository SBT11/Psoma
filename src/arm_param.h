#ifndef ARM_PARAM_H
#define ARM_PARAM_H

#include "fileparsers.h"

class arm_param
{
public:
    arm_param();
    arm_param(string aConfigFile);
    int load_params();
    void display_params();
    int check_params();

    string configFile;

    string trajectoryFile;
    double repeat_nb;
    double repeat_pause;
    double speed_max;
    double speed_min;
    double pos_sensitivity;

};

#endif // ARM_PARAM_H
