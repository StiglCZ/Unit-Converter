#ifndef TYPES_HH
#define TYPES_HH

#include <map>
#include <string>
#include <vector>
#include "weight.hh"
#include "length.hh"

const std::map<std::string, std::pair<std::vector<std::string>, std::vector<double>>> ConversionTypes = {
    {"Weight", {Weight_FormatNames, Weight_FormatValues}},
    {"Length", {Length_FormatNames, Length_FormatValues}},
};

#endif
