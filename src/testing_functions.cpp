# include "testing_functions.h"




void batch_sensor_rsp(int nb_repetitions)
{
    ofstream outputStream;
    outputStream.open("../data/sensor_rsp.dat");
    sensor_iit * aSensor = new sensor_iit[nb_repetitions];
    for (int s=0;s<nb_repetitions;s++)
    {
        aSensor[s].init_sensor(0,0,0);
    }
    for(int ax=-150;ax<150;ax++)
    {
        for (int s=0;s<nb_repetitions;s++)
        {
            outputStream << aSensor[s].get_2drsp((double)ax/10,0)  << "   ";
        }
        outputStream << endl;
    }
    outputStream.close();
}
