#include "mr_param.h"

mr_param::mr_param()
{
}

mr_param::mr_param(string aConfigFile)
{
    configFile = aConfigFile;
    clog << "Configuration file defined :  '" << configFile << "'" << endl;

    load_params();
    check_params();
    display_params();
}

int mr_param::load_params()
{
    nb_mr = confParser_int(configFile,"nb_mr");
    V_rest = confParser_int(configFile,"V_rest");
    C = confParser_int(configFile,"C");
    g = confParser_int(configFile,"g");
    I_gain = confParser_int(configFile,"I_gain");
    V_reset = confParser_int(configFile,"V_reset");
    t_refractory = confParser_int(configFile,"t_refractory");
    V_thresh = confParser_int(configFile,"V_thresh");
    V_thresh_incr = confParser_int(configFile,"V_thresh_incr");
    t_thresh = confParser_int(configFile,"t_thresh");
    dt = confParser_int(configFile,"dt");
    return 0;
}

void mr_param::display_params()
{
    clog << "nb_mr = " << nb_mr << endl;
    clog << "V_rest = " << V_rest << endl;
    clog << "C = " << C << endl;
    clog << "g = " << g << endl;
    clog << "I_gain = " << I_gain << endl;
    clog << "V_reset = " << V_reset << endl;
    clog << "t_refractory = " << t_refractory << endl;
    clog << "V_thresh = " << V_thresh << endl;
    clog << "V_thresh_incr = " << V_thresh_incr << endl;
    clog << "t_thresh = " << t_thresh << endl;
    clog << "dt = " << dt << endl;
}

int mr_param::check_params()
{
    int err = 0;
    if(nb_mr==PARS_ERR_INT)
    {
        nb_mr = 24;
        err = 1;
    }
    if(V_rest==PARS_ERR_INT)
    {
        V_rest = -70;
        err = 1;
    }
    if(C==PARS_ERR_INT)
    {
        C = 0.5;
        err = 1;
    }
    if(g==PARS_ERR_INT)
    {
        g = 25;
        err = 1;
    }
    if(I_gain==PARS_ERR_INT)
    {
        I_gain = -1e-10;
        err = 1;
    }
    if(V_reset==PARS_ERR_INT)
    {
        V_reset = -100;
        err = 1;
    }
    if(t_refractory==PARS_ERR_INT)
    {
        t_refractory = 2;
        err = 1;
    }
    if(V_thresh==PARS_ERR_INT)
    {
        V_thresh = -50;
        err = 1;
    }
    if(V_thresh_incr==PARS_ERR_INT)
    {
        V_thresh_incr = 50;
        err = 1;
    }
    if(t_thresh==PARS_ERR_INT)
    {
        t_thresh = 100;
        err = 1;
    }
    if(dt==PARS_ERR_INT)
    {
        dt = 1;
        err = 1;
    }

    return err;
}
