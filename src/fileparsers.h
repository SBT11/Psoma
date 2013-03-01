#ifndef FILEPARSERS_HPP
#define FILEPARSERS_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#define PARS_ERR_INT -123456
#define PARS_ERR_STR "-123456"

using namespace std;

float confParser_int(string aConfigFile, string aConfigParam);
string confParser_str(string aConfigFile, string aConfigParam);

#endif // FILEPARSERS_HPP
