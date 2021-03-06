#include "handbook.h"
#include <boost/regex.hpp>
#include <cstdlib>
#include <fstream>
#include "../errors/handbookerror.h"

Handbook *Handbook::__instance = 0;

Handbook *Handbook::instance() {
    if (!__instance) throw HandbookError("Handbook is not initialized");
    return __instance;
}

Handbook::Handbook(const char *configFileName) {
    if (__instance) {
        throw HandbookError("Handbook can be initialized just one time");
    }

    std::fstream configFile(configFileName);

    if (!configFile.is_open()) {
        throw HandbookError("Cannot open configuration file", configFileName);
    }

    boost::regex commentRegexp("^\\s*#");
    boost::regex sectionRegexp("^\\[(.+)\\]");
    boost::regex variableRegexp("^\\s*([\\(\\)A-Za-z0-9_-]+)\\s*=\\s*([\\d\\.e-]+)");

    VarVal *currentSection = 0;

    std::string line;
    boost::smatch matches;
    while (std::getline(configFile, line)) {
        if (line.length() == 0 || boost::regex_match(line, matches, commentRegexp)) continue;

        if (boost::regex_match(line, matches, sectionRegexp)) {
            std::string sectionName = matches[1].str();
            currentSection = &_values[sectionName];
        } else if (boost::regex_match(line, matches, variableRegexp)) {
            if (currentSection) {
                std::string variable = matches[1].str();
                double value = atof(matches[2].str().c_str());
                (*currentSection)[variable] = value;
            } else {
                throw HandbookError("Variable is not in section", line.c_str());
            }
        }
    }

    __instance = this;
}

double Handbook::value(const char *sectionName, const char *variableName) const {
    auto sectionPair = _values.find(sectionName);
    if (sectionPair != _values.cend()) {
        auto variablePair = sectionPair->second.find(variableName);
        if (variablePair != sectionPair->second.end()) {
            return variablePair->second;
        }
    }

    throw HandbookError("Variable not found", sectionName, variableName);
    return 0;
}

int Handbook::sizeX() const {
    return value("sizes", "x");
}

int Handbook::sizeY() const {
    return value("sizes", "y");
}
