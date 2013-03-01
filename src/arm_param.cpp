#include "arm_param.h"

arm_param::arm_param()
{
}

arm_param::arm_param(string aConfigFile)
{
    configFile = aConfigFile;
    clog << "Configuration file defined :  '" << configFile << "'" << endl;

    load_params();
    check_params();
    display_params();
}

int arm_param::load_params()
{
    repeat_nb = confParser_int(configFile,"repeat_nb");
    repeat_pause = confParser_int(configFile,"repeat_pause");
    speed_max = confParser_int(configFile,"speed_max");
    speed_min = confParser_int(configFile,"speed_min");
    trajectoryFile = confParser_str(configFile,"trajectoryFile");
    pos_sensitivity = confParser_int(configFile,"pos_sensitivity");

    return 0;
}

void arm_param::display_params()
{
    clog << "repeat_nb = " << repeat_nb << endl;
    clog << "repeat_pause = " << repeat_pause << endl;
    clog << "speed_max = " << speed_max << endl;
    clog << "speed_min = " << speed_min << endl;
    clog << "pos_sensitivity = " << pos_sensitivity << endl;
    clog << "trajectoryFile = '" << trajectoryFile << "'" << endl;
}

int arm_param::check_params()
{
    int err = 0;
    if(repeat_nb==PARS_ERR_INT)
    {
        repeat_nb = 1;
        err = 1;
    }
    if(repeat_pause==PARS_ERR_INT)
    {
        repeat_pause = 1;
        err = 1;
    }
    if(speed_max==PARS_ERR_INT)
    {
        speed_max = 80;
        err = 1;
    }
    if(speed_min==PARS_ERR_INT)
    {
        speed_min = 10;
        err = 1;
    }
    if(pos_sensitivity==PARS_ERR_INT)
    {
        pos_sensitivity = 0.1;
        err = 1;
    }
    if(trajectoryFile==PARS_ERR_STR)
    {
        trajectoryFile = "../net/arm.trj";
        err = 1;
    }

    return err;
}
