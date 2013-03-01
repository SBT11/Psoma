#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <vector>

#include "mc_param.h"
#include "mr_param.h"
#include "psoma_param.h"
#include "arm_param.h"

#define configFile "../config/psoma.conf"

#ifdef _WIN32
    //define something specific for Windows
#else
    //define something specific for an Unix
#endif

struct stimulus
{
    double x;
    double y;
    double z;
};


extern psoma_param SWparams;
extern mc_param MCparams;
extern mr_param MRparams;
extern arm_param ARMparams;
extern vector<stimulus> sti_vect;

#endif // GLOBAL_H
