#include "arm.h"

arm::arm()
{

    trajectory = network_co();
    trajectory.networkParser(ARMparams.trajectoryFile);

    if(trajectory.m>1)
    {
        x = trajectory.net[0][0];
        y = trajectory.net[0][1];
        z = trajectory.net[0][2];
        v = trajectory.net[0][3];   // no acceleration phase for start of movement

        double norm = sqrt(pow(trajectory.net[1][0] - x,2) + pow(trajectory.net[1][1] - y,2) + pow(trajectory.net[1][2] - z,2));
        if(norm>0)
        {
            dir_x = (trajectory.net[1][0] - x)/norm;
            dir_y = (trajectory.net[1][1] - y)/norm;
            dir_z = (trajectory.net[1][2] - z)/norm;
        }
        else
        {
            dir_x = 0;
            dir_y = 0;
            dir_z = 0;
        }
    }

    timeOfPause = -1;
    durationOfPause = 0;
    time = 0;
    trajSegment = 1;
    trajCount = 0;
    outputSave = 0;
    segmentEndIndicator = 0;

    if(trajectory.net[1][4]==1)
    {
        timeOfPause = time;
        durationOfPause = trajectory.net[1][3];
    }

}

arm::~arm()
{
    if(outputStream.is_open())
    {
        outputStream.close();
    }
}

void arm::changeSegment(double atime)
{
    if (trajSegment==trajectory.m-1)   // if past segment was the last of the trajectory: start again
    {
        trajSegment = 0;
        trajCount++;
        clog << "Starting trajectory repetition n°" << trajCount << endl;
    }
    else
    {
        trajSegment++;
        clog << "Starting trajectory segment n°" << trajSegment << endl;
    }

    while(trajectory.net[trajSegment][4]==-1 && trajSegment<trajectory.m)   // if teleport to point was set
    {
        x = trajectory.net[trajSegment][0];
        y = trajectory.net[trajSegment][1];
        z = trajectory.net[trajSegment][2];
        v = trajectory.net[trajSegment][3];   // no acceleration phase for start of movement

        trajSegment++;
    }

    if(trajectory.net[trajSegment][4]==1)
    {
        timeOfPause = atime;
        durationOfPause = trajectory.net[trajSegment][3];
    }

    double norm = sqrt(pow(trajectory.net[trajSegment][0] - x,2) + pow(trajectory.net[trajSegment][1] - y,2) + pow(trajectory.net[trajSegment][2] - z,2));
    if(norm>0)
    {
        dir_x = (trajectory.net[trajSegment][0] - x)/norm;
        dir_y = (trajectory.net[trajSegment][1] - y)/norm;
        dir_z = (trajectory.net[trajSegment][2] - z)/norm;
    }
    else
    {
        dir_x = 0;
        dir_y = 0;
        dir_z = 0;
    }

    v = trajectory.net[trajSegment][3];   // no acceleration phase for start of movement
}

void arm::run(double atime)
{
    // update direction too ?


    if(atime - timeOfPause > durationOfPause)
    {
        if(segmentEndIndicator==1)
        {
            changeSegment(atime);
        }
        else
        {
            double dt = atime - time; // (in ms)
            x = x + v * dir_x * dt / 1000;
            y = y + v * dir_y * dt / 1000;
            z = z + v * dir_z * dt / 1000;
        }

        if(checkSegmentEnd())
            segmentEndIndicator = 1;
        else
            segmentEndIndicator = 0;

    }

    time = atime;

    if(checkRepeatEnd()==0)
        saveOutput();

}

int arm::checkSegmentEnd()
{
    if ( (abs(trajectory.net[trajSegment][0] - x)<=ARMparams.pos_sensitivity) & (abs(trajectory.net[trajSegment][1] - y)<=ARMparams.pos_sensitivity) & (abs(trajectory.net[trajSegment][2] - z)<=ARMparams.pos_sensitivity) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int arm::checkRepeatEnd()
{
    return (trajCount>ARMparams.repeat_nb-1);
}

int arm::initOutput(string fileName)
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

int arm::saveOutput()
{
    if(outputSave==1)
    {
        // time (ms), posX (mm), posY,posZ,vX (mm/s),vY,vZ, trajectory segment index,trajectory repeat index
        outputStream << time << " " << x << " " << y << " " << z << " " << v * dir_x << " " << v * dir_y << " " << v * dir_z << " " << trajCount << " " << trajSegment << endl;
    }
    return 0;
}
