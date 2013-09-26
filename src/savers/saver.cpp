#include "saver.h"
#include <sstream>
#include "../errors/parse_error.h"

Saver::Saver(const char *outFileName) : _outFile(outFileName) {
    if (!_outFile) {
        std::stringstream ss;
        ss << "File \"" << outFileName << "\" couldn't be created\n";
        throw ParseError(ss.str().c_str());
    }
}

Saver::~Saver() {
    _outFile.close();
}
