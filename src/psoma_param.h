#ifndef PSOMA_PARAM_H
#define PSOMA_PARAM_H

#include<string>
#include<iostream>

#include"fileparsers.h"

/***
*
*   Parameters for Program
*
***/

class psoma_param
{
public:
    psoma_param();
    psoma_param(string aConfigFile);
    int load_params();
    void display_params();
    int check_params();

    string configFile;

    string mr_paramFile;
    string mc_paramFile;
    string mc2mr_netFile;
    string arm_paramFile;
    string sti_netFile;
    string analog_saveFile;
    string traj_saveFile;
    string LIFspike_saveFile;
    string LIFdyn_saveFile;
    double time_step;
};

#endif // PSOMA_PARAM_H
