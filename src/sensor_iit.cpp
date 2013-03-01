#include "sensor_iit.h"

sensor_iit::sensor_iit()
{

}

sensor_iit::sensor_iit(double ax, double ay, double az)
{
    init_sensor(ax,ay,az);
}

void sensor_iit::init_sensor(double ax, double ay, double az)
{
    x = ax;
    y = ay;
    z = az;
    pi = atan(1.0)*4;
}

double sensor_iit::get_WN(double boundry)
{
    return boundry * (2 * (double)rand() / RAND_MAX - 1) ;
}

double sensor_iit::get_GN(double amean, double astd)
{
    double U = (double)rand() / RAND_MAX;
    double V = (double)rand() / RAND_MAX;

    return sqrt(-2*log(U))*cos(2*pi*V) * astd + amean;
}

double sensor_iit::get_2drsp(double sti_x, double sti_y)
{
    double amp = MCparams.rsp_amp + get_WN(MCparams.rsp_amp_wn);
    double width = MCparams.rsp_width + get_WN(MCparams.rsp_width_wn);
    return amp * exp( - (pow(x-sti_x,2) + pow(y-sti_y,2)) / (2 * pow(width,2)));
}

double sensor_iit::get_3drsp(double sti_x, double sti_y, double sti_z)
{
    double amp = MCparams.rsp_amp + get_WN(MCparams.rsp_amp_wn);
    double width = MCparams.rsp_width + get_WN(MCparams.rsp_width_wn);
    //return amp * exp( - (pow(x-sti_x,2) + pow(y-sti_y,2) + pow(z-sti_z,2)) / (2 * pow(width,2)));    // better integrate Z coordinate (with a specific width for z coordinates)
    return amp *  (1 - ((double)(abs(sti_z - z)))/100) * exp( - (pow(x-sti_x,2) + pow(y-sti_y,2)) / (2 * pow(width,2))); // carfelu, bug if sti_z-z > 100 ...
}

void sensor_iit::set_2dpos(double new_x, double new_y)
{
    x = new_x;
    y = new_y;
}

void sensor_iit::set_3dpos(double new_x, double new_y, double new_z)
{
    x = new_x;
    y = new_y;
    z = new_z;
}

void sensor_iit::move_2dpos(double dx, double dy)
{
    x = x + dx;
    y = y + dy;
}
