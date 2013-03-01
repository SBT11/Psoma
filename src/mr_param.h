#ifndef MR_PARAM_H
#define MR_PARAM_H

#include<string>
#include<iostream>

#include"fileparsers.h"

/***
*
*   Parameters for Mechanoreceptors (aka. LIF)
*
***/

class mr_param
{
public:
    mr_param();
    mr_param(string aConfigFile);
    int load_params();
    void display_params();
    int check_params();

    string configFile;

    double nb_mr;
    double V_rest;
    double C;
    double g;
    double I_gain;
    double V_reset;
    double t_refractory;
    double V_thresh;
    double V_thresh_incr;
    double t_thresh;
    double dt;
};

#endif // MR_PARAM_H
