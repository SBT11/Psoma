#ifndef ARM_H
#define ARM_H

#include <math.h>
#include <cmath>

#include "network_co.h"
#include "global.h"

class arm
{
public:
    arm();
    ~arm();
    void changeSegment(double atime);
    void setSpeed(double aspeed);
    void run(double atime);
    int checkSegmentEnd();
    int checkRepeatEnd();   //checks if the number of repetitions of the trajectory has been reached
    int initOutput(string fileName);
    int saveOutput(); // time (ms), posX (mm), posY,posZ,vX (mm/s),vY,vZ, trajectory segment index,trajectory repeat index


    double time; // ms
    double x;   // mm
    double y;   // mm
    double z;   // mm
    double dir_x;   // x projection of normalized direction vector
    double dir_y;   // y projection of normalized direction vector
    double dir_z;   // z projection of normalized direction vector
    double v;   // speed in mm/s
    int durationOfPause;   // duration of pause
    int timeOfPause; // time when pause signal was sent
    int trajSegment;    // trajectory segment currently being followed, starts at 0
    int trajCount;      // counts the number of times the trajectory was repeated (starts at 0)
    int segmentEndIndicator; // indicates that the end of a segment has been reached during last run
    ofstream outputStream;    // stream to save output
    int outputSave;         // 0=do not save, 1=save output to file
    network_co trajectory;

};

#endif // ARM_H
