#include "mc_param.h"

mc_param::mc_param()
{
}

mc_param::mc_param(string aConfigFile)
{
    configFile = aConfigFile;
    clog << "Configuration file defined :  '" << configFile << "'" << endl;

    load_params();
    check_params();
    display_params();
}

int mc_param::load_params()
{
    nb_sensors = confParser_int(configFile,"nb_sensors");
    rsp_amp = confParser_int(configFile,"rsp_amp");
    rsp_width = confParser_int(configFile,"rsp_width");
    rsp_amp_wn = confParser_int(configFile,"rsp_amp_wn");
    rsp_width_wn = confParser_int(configFile,"rsp_width_wn");
    mc_layoutFile = confParser_str(configFile,"mc_layoutFile");

    return 0;
}

void mc_param::display_params()
{
    clog << "nb_sensors = " << nb_sensors << endl;
    clog << "rsp_amp = " << rsp_amp << endl;
    clog << "rsp_width = " << rsp_width << endl;
    clog << "rsp_amp_wn = " << rsp_amp_wn << endl;
    clog << "rsp_width_wn = " << rsp_width_wn << endl;
    clog << "mc_layoutFile = '" << mc_layoutFile << "'" << endl;
}

int mc_param::check_params()
{
    int err = 0;
    if(nb_sensors==PARS_ERR_INT)
    {
        nb_sensors = 1;
        err = 1;
    }
    if(rsp_amp==PARS_ERR_INT)
    {
        rsp_amp = 43;
        err = 1;
    }
    if(rsp_width==PARS_ERR_INT)
    {
        rsp_width = 2.9;
        err = 1;
    }
    if(rsp_amp_wn==PARS_ERR_INT)
    {
        rsp_amp_wn = 8.9;
        err = 1;
    }
    if(rsp_width_wn==PARS_ERR_INT)
    {
        rsp_width_wn = 0.32;
        err = 1;
    }
    if(mc_layoutFile==PARS_ERR_STR)
    {
        mc_layoutFile = "../net/fingertip_layout.pos";
        err = 1;
    }

    return err;
}
