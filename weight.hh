#ifndef WEIGHT_HH
#define WEIGHT_HH

#include <vector>
#include <string>
const std::vector<std::string> Weight_FormatNames = {
    "nanogram",
    "microgram",
    "milligram",
    "centigram",
    "decigram",
    "carat",
    "gram",
    "kilogram",
    "megagram",
    "gigagram",
};

const std::vector<double> Weight_FormatValues = {
    1.000e+0,
    1.000e+3,
    1.000e+6,
    1.000e+7,
    1.000e+8,
    2.000e+8,
    
    1.000e+9,
    1.000e+12,
    1.000e+15,
    1.000e+18,
    
};

#endif
