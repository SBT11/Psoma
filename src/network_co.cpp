#include "network_co.h"

network_co::network_co()
{
    n = -1;
    m = -1;
    nb_cell1 = -1;
    nb_cell2 = -1;
    net = NULL;
}

network_co::~network_co()
{
    if(net!=NULL)
    {
        for(int i=0;i<m;i++)
        {
            delete[] net[i];
        }
        delete[] net;
    }
}

int network_co::networkParser(string netFile)
{
    ifstream netFILE ( netFile.c_str() );
    stringstream tmp_stream;
    bool isFirstLine = true;
    int i_m = 0;
    int lineCounter = 0;

    if ( netFILE.is_open() )
    {
        string line;
        while ( getline ( netFILE, line ) )
        {
            lineCounter++;
            string::size_type i = line.find_first_not_of ( " \t\n\v" );
            if ( i != string::npos  && line[0]!='#')
            {
                if ( isFirstLine )
                {
                    tmp_stream.str(line);
                    tmp_stream >> m >> n;
                    if( allocateNet()==1 )
                    {
                        netFILE.close();
                        return 1;
                    }
                    isFirstLine = false;
                }
                else
                {
                    tmp_stream.clear();
                    tmp_stream.str(line);
                    for ( int i_n=0;(i_n<(unsigned int)n) & (i_m < m) ;i_n++)
                    {
                        if ( !tmp_stream.eof() )
                        {
                            tmp_stream >> net[i_m][i_n];
                        }
                        else
                        {
                            cerr << "ERROR - reading file '" << netFile << "', line " << lineCounter << ": not enough array elements" << endl;
                            deallocateNet();
                            netFILE.close();
                            return 1;
                        }
                    }
                    i_m++;
                    if( i_m>m )
                    {
                        cerr << "WARNING - reading file '" << netFile << "', more informative lines than specified in array dimensions: surplus lines have been discarded" << endl;
                    }
                }
            }
        }
        netFILE.close();

        if ( i_m<m)
        {
            cerr << "ERROR - reading file '" << netFile << "': not enough informative lines to file the indicated array size (" << m << "x" << n << ")" << endl;
            deallocateNet();
            netFILE.close();
            return 1;
        }
        return getNbCells();
    }
    else
    {
        cerr << "ERROR - file not found :  '" << netFile <<"'" << endl;
        return 1;
    }
}

int network_co::allocateNet()
{
    if ( (m>0) & (n>0) )
    {
        net = new double*[m];
        for ( int i=0; i<m; i++ )
        {
            net[i] = new double[n];
        }
        return 0;
    }
    else
    {
        n = -1;
        m = -1;
        net = NULL;
        cerr << "ERROR - could not allocate array with dimensions: " << m << "x" << n << endl;
        return 1;
    }
}

void network_co::deallocateNet()
{
    if(net!=NULL)
    {
        for(int i=0;i<m;i++)
        {
            delete[] net[i];
        }
        delete[] net;
    }

    n = -1;
    m = -1;
    net = NULL;
}

void network_co::displayNet(ostream &stream)
{
    if( net != NULL )
    {
        for ( int i=0;i<m;i++ )
        {
            for ( int j=0;j<n;j++ )
            {
                stream << net[i][j] << "  ";
            }
            stream << endl;
        }
    }
    else
    {
        cerr << "WARNING - could not display array as it is has not been allocated" << endl;
    }
}

int network_co::getNbCells()
{
    int max1 = 0;
    int max2 = 0;
    if ( (net!=NULL) & (n>=2) )
    {
        for ( int i=0;i<m;i++ )
        {
            if ( max1<net[i][0] )
                max1 = net[i][0];
            if ( max2<net[i][1] )
                max2 = net[i][1];
        }
        nb_cell1 = max1 + 1;
        nb_cell2 = max2 + 1;
        return 0;
    }
    else
    {
            cerr << "WARNING - unable to count number of cells in network as array has not been allocated" << endl;
            return 1;
    }
}

int network_co::checkNbCells(int aCell1, int aCell2)
{
    int out = 0;
    if ( nb_cell1!=aCell1 )
    {
        out++;
        cerr << "WARNING - inconsistent number of cells between configuration file and network file" << endl;
    }
    if ( nb_cell2!=aCell2 )
    {
        out++;
        cerr << "WARNING - inconsistent number of cells between configuration file and network file" << endl;
    }
    return out;
}
