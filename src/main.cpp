#include "main.h"

using namespace std;

int main()
{
    clog << "Starting PSoma ..." << endl;
    srand ( time(NULL) );   // initializing random generators

    clog << "Reading configuration files ..." << endl;
    SWparams = psoma_param(configFile);
    MCparams = mc_param(SWparams.mc_paramFile);
    MRparams = mr_param(SWparams.mr_paramFile);
    ARMparams = arm_param(SWparams.arm_paramFile);

    clog << "Reading network files ..." << endl;

    clog << "Initializing simulation components ..." << endl;
    loadStimuli();

    clog << "Running simulation ..." << endl;
    run();

    clog << "Quitting PSoma ..." << endl;
cout << "pause";
    return 0;
}

int run()
{
    double time = 0;
    arm zeArm;
    fingertip zeFingertip;
    lifnetwork zeLifnetwork;

    zeFingertip.initOutput(SWparams.analog_saveFile);
    zeArm.initOutput(SWparams.traj_saveFile);
    zeLifnetwork.initLifSpikeOutput(SWparams.LIFspike_saveFile);
    zeLifnetwork.initLifDynamicsOutput(SWparams.LIFdyn_saveFile);

    while(zeArm.checkRepeatEnd()==0)
    {
        zeArm.run(time);

        zeFingertip.set_3dpos(zeArm.x,zeArm.y,zeArm.z);
        zeFingertip.run(time);

        zeLifnetwork.run(time,zeFingertip.sensorRsp);

        time = time + SWparams.time_step;
    }

    return 0;
}

int loadStimuli()
{
    network_co net_sti = network_co();
    net_sti.networkParser(SWparams.sti_netFile);

    stimulus asti;
    for(int i=0;i<net_sti.m;i++)
    {
        asti.x = net_sti.net[i][0];
        asti.y = net_sti.net[i][1];
        asti.z = net_sti.net[i][2];
        sti_vect.push_back(asti);
    }

    return 0;
}
