#include "fileparsers.h"


using namespace std;

float confParser_int(string aConfigFile, string aConfigParam)
{
    ifstream confFILE ( aConfigFile.c_str() );
    stringstream tmp_stream;
    string tmp_string;
    bool discard = false;

    if ( confFILE.is_open() )
    {
        string line;
        while ( getline ( confFILE, line ) )
        {
            discard = false;
            tmp_string.clear();
            string::size_type i = line.find_first_not_of ( " \t\n\v" );
            if ( i != string::npos  && line[0]!='#')
            {
                tmp_stream.str(line);
                while (tmp_stream >> tmp_string && !discard)
                {
                    if (tmp_string[0]!='#' && tmp_string.compare(aConfigParam)==0)
                    {
                        float result;
                        tmp_stream >> result;
                        confFILE.close();
                        return result;
                    }
                    else
                    {
                        discard = true;
                    }
                }
            }
        }
        confFILE.close();
        cerr << "ERROR - Parameter not found in file : '" << aConfigParam << "'      (will be using default value)" << endl;
    }
    else
    {
        cerr << "ERROR - configuration file not found :  '" << aConfigFile <<"'" << endl;
    }
    return -123456;
}


string confParser_str(string aConfigFile, string aConfigParam)
{
    ifstream confFILE ( aConfigFile.c_str() );
    stringstream tmp_stream;
    string tmp_string;
    bool discard = false;

    if ( confFILE.is_open() )
    {
        string line;
        while ( getline ( confFILE, line ) )
        {
            discard = false;
            tmp_string.clear();
            string::size_type i = line.find_first_not_of ( " \t\n" /*" \t\n\v"*/ );
            if ( i != string::npos && line[0]!='#')
            {
                tmp_stream.str(line);
                while (tmp_stream >> tmp_string && !discard)
                {
                    if (tmp_string[0]!='#' && tmp_string.compare(aConfigParam)==0)
                    {
                        string result;
                        tmp_stream >> result;
                        confFILE.close();
                        return result;
                    }
                    else
                    {
                        discard = true;
                    }
                }
            }
        }
        confFILE.close();
        cerr << "ERROR - Parameter not found in file : '" << aConfigParam << "'      (will be using default value)" << endl;
    }
    else
    {
        cerr << "ERROR - configuration file not found :  '" << aConfigFile <<"'" << endl;
    }
    return "-123456";
}
