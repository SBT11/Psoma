#include "fingertip.h"

fingertip::fingertip()
{
    x = 0;
    y = 0;
    z = 0;

    outputSave = 0;
    nb_sensors = MCparams.nb_sensors;

    layout = network_co();
    layout.networkParser(MCparams.mc_layoutFile);

    if (layout.n<4)
    {
        cerr << "ERROR - insufficient number of dimensions (x,y,z) in fingertip layout file" << endl;
        return;
    }
    if (nb_sensors!=layout.nb_cell1)
    {
        cerr << "WARNING - inconsistent number of sensors between configuration file and fingertip layout file - choosing layout file value : " << layout.nb_cell1 << endl;
        nb_sensors = layout.nb_cell1;
    }

    sensors = new sensor_iit[nb_sensors];
    sensorRsp = new double[nb_sensors];
    for (int l=0;l<layout.m;l++)
    {
        sensors[(int)layout.net[l][0]].init_sensor(layout.net[l][1],layout.net[l][2],layout.net[l][3]);
        sensorRsp[l] = 0;
    }

}

fingertip::~fingertip()
{
    delete[] sensors;
    delete[] sensorRsp;
    if(outputStream.is_open())
        outputStream.close();
}

void fingertip::set_2dpos(double new_x, double new_y)
{
    x = new_x;
    y = new_y;
    for (int l=0;l<layout.m;l++)
    {
        sensors[(int)layout.net[l][0]].set_2dpos(layout.net[l][1] + x,layout.net[l][2] + y);
    }
}

void fingertip::set_3dpos(double new_x, double new_y, double new_z)
{
    x = new_x;
    y = new_y;
    z = new_z;
    for (int l=0;l<layout.m;l++)
    {
        sensors[(int)layout.net[l][0]].set_3dpos(layout.net[l][1] + x,layout.net[l][2] + y, z); // no pitch/roll etc for the finger, possibly add them to layout file ...
    }
}

void fingertip::move_2dpos(double dx, double dy)
{
    x = x + dx;
    y = y + dy;
    for (int l=0;l<layout.m;l++)
    {
        sensors[(int)layout.net[l][0]].move_2dpos(dx,dy);
    }
}

int fingertip::initOutput(string fileName)
{
    if((bool)(outputSave==0) & !outputStream.is_open())
    {
        outputSave=1;
        outputStream.open(fileName.c_str());
    }
    else
    {
        outputStream.close();
        outputStream.open(fileName.c_str());
    }

    if(!outputStream.is_open())
    {
        outputSave=0;
        return 1;
    }
    else
    {
        return 0;
    }
}

int fingertip::saveOutput()
{
    if(outputSave==1)
    {
        outputStream << time << " ";
        for ( int i=0;i<nb_sensors; i++ )
        {
            outputStream << (int)sensorRsp[i] << " ";
        }
        outputStream << endl;
    }
    return 0;
}

int fingertip::run(double atime)
{
    time = atime;

    for(int i=0;i<nb_sensors;i++)
    {
        sensorRsp[i] = 0;
        for(unsigned int j=0;j<sti_vect.size();j++)
        {
            sensorRsp[i] = sensorRsp[i] + sensors[i].get_3drsp(sti_vect[j].x,sti_vect[j].y,sti_vect[j].z); // for now just adds the effects of the different stimuli
        }
    }
    saveOutput();
    return 0;
}
