#include "psoma_param.h"

psoma_param::psoma_param()
{
}

psoma_param::psoma_param(string aConfigFile)
{
    configFile = aConfigFile;
    clog << "Configuration file defined :  '" << configFile << "'" << endl;

    load_params();
    check_params();
    display_params();
}

int psoma_param::load_params()
{
    mc_paramFile = confParser_str(configFile,"mc_paramFile");
    mr_paramFile = confParser_str(configFile,"mr_paramFile");
    mc2mr_netFile = confParser_str(configFile,"mc2mr_netFile");
    arm_paramFile = confParser_str(configFile,"arm_paramFile");
    sti_netFile = confParser_str(configFile,"sti_netFile");
    time_step = confParser_int(configFile,"time_step");
    analog_saveFile = confParser_str(configFile,"analog_saveFile");
    traj_saveFile = confParser_str(configFile,"traj_saveFile");
    LIFspike_saveFile = confParser_str(configFile,"LIFspike_saveFile");
    LIFdyn_saveFile = confParser_str(configFile,"LIFdyn_saveFile");

    return 0;
}

void psoma_param::display_params()
{
    clog << "mc_paramFile = '" << mc_paramFile << "'" << endl;
    clog << "mr_paramFile = '" << mr_paramFile << "'" << endl;
    clog << "arm_paramFile = '" << arm_paramFile << "'" << endl;
    clog << "mc2mr_netFile = '" << mc2mr_netFile << "'" << endl;
    clog << "sti_netFile = '" << sti_netFile << "'" << endl;
    clog << "time_step = " << time_step << endl;
    clog << "analog_saveFile = '" << analog_saveFile << "'" << endl;
    clog << "traj_saveFile = '" << traj_saveFile << "'" << endl;
    clog << "LIFspike_saveFile = '" << LIFspike_saveFile << "'" << endl;
    clog << "LIFdyn_saveFile = '" << LIFdyn_saveFile << "'" << endl;
}

int psoma_param::check_params()
{
    int err = 0;
    if(mc_paramFile==PARS_ERR_STR)
    {
        mc_paramFile = "../config/psoma_mr.conf";
        err = 1;
    }
    if(mr_paramFile==PARS_ERR_STR)
    {
        mr_paramFile = "../config/psoma_mr.conf";
        err = 1;
    }
    if(arm_paramFile==PARS_ERR_STR)
    {
        arm_paramFile = "../config/arm.conf";
        err = 1;
    }
    if(mc2mr_netFile==PARS_ERR_STR)
    {
        mc2mr_netFile = "../net/sensor2mr.net";
        err = 1;
    }
    if(sti_netFile==PARS_ERR_STR)
    {
        sti_netFile = "../net/stimuli.pos";
        err = 1;
    }
    if(time_step==PARS_ERR_INT)
    {
        time_step = 1;
        err = 1;
    }
    if(analog_saveFile==PARS_ERR_STR)
    {
        analog_saveFile = "../data/mat.dat";
        err = 1;
    }
    if(traj_saveFile==PARS_ERR_STR)
    {
        traj_saveFile = "../data/traj.dat";
        err = 1;
    }
    if(LIFspike_saveFile==PARS_ERR_STR)
    {
        LIFspike_saveFile = "../data/LIF_spike.dat";
        err = 1;
    }
    if(LIFdyn_saveFile==PARS_ERR_STR)
    {
        LIFdyn_saveFile = "../data/LIFdynamics/MR";
        err = 1;
    }

    return err;
}
