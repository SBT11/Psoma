#include "lifneuron.h"

lifneuron::lifneuron()
{
    v = MRparams.V_rest;
    vt = MRparams.V_thresh;
    time = 0;
    dt = MRparams.dt;
    last_I = 0;
    outputSave = 0;
    last_I_RK = 0;
}

lifneuron::~lifneuron()
{
    if(outputStream.is_open())
    {
        outputStream.close();
    }
}

int lifneuron::potential_dynamics(double I)
{
    v = v + (-1 * MRparams.g * 1e-09 * v + MRparams.g * 1e-09 * MRparams.V_rest - MRparams.I_gain * I * 1e3) / (MRparams.C * 1e-09) * dt * 1e-03;
    return 0;
}


int lifneuron::threshold_dynamics()
{
    vt = vt - (vt - MRparams.V_thresh) * dt / MRparams.t_thresh;
    // TODO : perhaps add an upper bound for vt!!!
    return 0;
}

int lifneuron::I_interpolation(double I,double aTime)
{
    int nb_i = (int)((aTime - time) / dt);
    if(nb_i>=0)
    {
        double a = (I - last_I)/(aTime - time);
        double b = last_I;
        for(int i=1;i<nb_i+1;i++)
        {
            vect_i.push_back(a * i * dt + b);
            vect_t.push_back(i * dt + time);
        }

        last_I = I;
        time = time + nb_i * dt;

        return 0;
    }
    else
    {
        cerr << "ERROR - LIF neurons: negative time evolution ('" << aTime - time << "ms')" << endl;
        return 1;
    }
}

int lifneuron::spiking_dynamics(double aTime)
{
    if(v>=vt)   // spike
    {
        v = MRparams.V_reset;   // resetting
        vt = vt + MRparams.V_thresh_incr;   // incressing potential threshold
        vect_spike.push_back(aTime);
    }
    return 0;
}

int lifneuron::run(double I, double aTime)
{
    I_interpolation(I,aTime);
    int n = vect_t.size();
    for(int i=0;i<n;i++)
    {
        if(vect_spike.size()==0 || vect_t.front()>vect_spike.back()+MRparams.t_refractory)
        {
            //potential_dynamics(vect_i.front());       // Euler version
            potential_dynamics_RK(vect_i.front());      // Runge-Kutta method
        }
        threshold_dynamics();
        spiking_dynamics(vect_t.front());

        saveOutput();

        vect_i.erase(vect_i.begin());
        vect_t.erase(vect_t.begin());
    }

    return 0;
}

int lifneuron::initOutput(string fileName)
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

int lifneuron::saveOutput()
{
    if(outputSave==1)
    {
        bool s;
        if(vect_spike.size()!=0)
        {
            s = (vect_t.front()==vect_spike.back());
        }
        else
        {
            s = 0;
        }
        outputStream << vect_t.front() << " " << vect_i.front() << " " << v << " " <<  vt << " " << s << endl;
        outputStream.flush();
    }
    return 0;
}

double lifneuron::potential_diff_equation(double I, double y)
{
    return (-1 * MRparams.g * 1e-09 * y + MRparams.g * 1e-09 * MRparams.V_rest - MRparams.I_gain * I * 1e3) / (MRparams.C * 1e-09);
}

int lifneuron::potential_dynamics_RK(double I)
{
    double Idir = (I-last_I_RK)/dt;
    double k1 = dt*1e-03 * potential_diff_equation(last_I_RK,v);
    double k2 = dt*1e-03 * potential_diff_equation(last_I_RK + 1/2*Idir*dt*1e-03,v+1/2*k1);
    double k3 = dt*1e-03 * potential_diff_equation(last_I_RK + 1/2*Idir*dt*1e-03,v+1/2*k2);
    double k4 = dt*1e-03 * potential_diff_equation(last_I_RK + Idir*dt*1e-03,v+k3);
    v = v + 1.0/6.0 * (k1 + 2*k2 + 2*k3 + k4);
    last_I_RK = I;
    return 0;
}
