#ifndef NETWORK_CO_H
#define NETWORK_CO_H

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

class network_co
{
public:
    network_co();
    ~network_co();
    int networkParser(string netFile);
    int allocateNet();
    void deallocateNet();
    void displayNet(ostream &stream);
    int getNbCells();
    int checkNbCells(int aCell1, int aCell2);

    int n; // size on dimension 1 (nb lines) => nb of connections
    int m; // size on dimension 2 (nb columns)  => nb of parameters per connection
    double ** net;  // connectivity matrix + possibly connection weight + connection delay
    int nb_cell1;
    int nb_cell2;
};

#endif // NETWORK_CO_H
