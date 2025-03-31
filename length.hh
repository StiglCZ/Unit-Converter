#ifndef LENGTH_HH
#define LENGTH_HH

#include <vector>
#include <string>
const std::vector<std::string> Length_FormatNames = {
    "nanometers",
    "micrometers",
    "millimeters",
    "centimeters",
    "inches",
    "feet",
    "yards",
    "meters",
    "decameter",
    "kilometers",
    "miles",
    "megameters",
    "gigameters",
    "lightyears",
};

const std::vector<double> Length_FormatValues = {
    1.000e+0,
    1.000e+3,
    1.000e+6,
    1.000e+7,
    
    2.540e+7,
    3.048e+8,
    9.144e+8,
    
    1.000e+9,
    1.000e+10,
    1.000e+12,
    
    1.609344e+12,
    
    1.000e+15,
    1.000e+18,
    9.4607e+24,
};

#endif
