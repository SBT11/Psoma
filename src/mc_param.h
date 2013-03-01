#ifndef MC_PARAM_H
#define MC_PARAM_H

#include<string>
#include<iostream>

#include"fileparsers.h"

using namespace std;

/***
*
*   Parameters for sensors (aka. Merkel Cells)
*
***/

class mc_param
{
public:
    mc_param();
    mc_param(string aConfigFile);
    int load_params();
    void display_params();
    int check_params();

    string configFile;
    string mc_layoutFile;       // file with sensor positions on fingertip

    double nb_sensors;         // number of sensors
    double rsp_amp;    // amplitude of response
    double rsp_width;  // width of response
    double rsp_amp_wn;  // white noise on amplitude of response
    double rsp_width_wn;    // white noise on width of response
};

#endif // MC_PARAM_H
