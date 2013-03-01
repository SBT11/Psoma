#include "lifnetwork.h"

lifnetwork::lifnetwork()
{
    outputSpikeSave = 0;
    outputDynamicsSave = 0;

    net_mc2mr = network_co();
    net_mc2mr.networkParser(SWparams.mc2mr_netFile);
    net_mc2mr.checkNbCells(MCparams.nb_sensors,MRparams.nb_mr);

    time = 0;
    nb_mr = (int)MRparams.nb_mr;
    lifarray = new lifneuron[nb_mr];
}

lifnetwork::~lifnetwork()
{
    delete[] lifarray;
    if(outputSpikeStream.is_open())
    {
        outputSpikeStream.close();
    }
}

int lifnetwork::run(double atime,double * sensor_array)
{
    double * i_array = new double[nb_mr];
    for (int i=0;i<nb_mr;i++)
    {
        i_array[i] = 0;
    }

    for (int i=0;i<net_mc2mr.m;i++)
    {
        if(net_mc2mr.net[i][1]<nb_mr)
        {
            i_array[(int)net_mc2mr.net[i][1]] = i_array[(int)net_mc2mr.net[i][1]] + sensor_array[(int)net_mc2mr.net[i][0]]*net_mc2mr.net[i][2];    // no time delay for now
        }
        else
        {
            cerr << "ERROR - index is out of bounds in MR2MC net" << endl;
        }
    }

    for (int i=0;i<nb_mr;i++)
    {
        lifarray[i].run(i_array[i],time);
    }
    time = atime;
    saveLifSpikeOutput();

    delete[] i_array;
    return 0;

}

int lifnetwork::initLifDynamicsOutput(string fileName)
{
    stringstream ss;
    int out = 0;
    for (int i=0;i<nb_mr;i++)
    {
        ss.str(std::string());
        ss << fileName << i << ".dat";
        out = out + lifarray[i].initOutput(ss.str());
    }

    return out;
}

int lifnetwork::initLifSpikeOutput(string fileName)
{
    if((bool)(outputSpikeSave==0) & !outputSpikeStream.is_open())
    {
        outputSpikeSave=1;
        outputSpikeStream.open(fileName.c_str());
    }
    else
    {
        outputSpikeStream.close();
        outputSpikeStream.open(fileName.c_str());
    }

    if(!outputSpikeStream.is_open())
    {
        outputSpikeSave=0;
        return 1;
    }
    else
    {
        return 0;
    }
}

int lifnetwork::saveLifSpikeOutput()
{
    if(outputSpikeSave==1)
    {

        for (int i = 0;i<nb_mr;i++)
        {
            for(unsigned int j=0;j<lifarray[i].vect_spike.size();j++)
            {
                outputSpikeStream << lifarray[i].vect_spike.at(j) << "  " << i << endl;   // would be nice to find a way to incert the two loops, perhaps make lif save to the same buffer ... but no difference if tmestep is 1ms
            }
            lifarray[i].vect_spike.clear();
        }
    }
    return 0;
}
