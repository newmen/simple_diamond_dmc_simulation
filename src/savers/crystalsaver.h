#ifndef CRYSTALSAVER_H
#define CRYSTALSAVER_H

#include "../surface/crystal.h"
#include "saver.h"

class CrystalSaver : public Saver
{
public:
    CrystalSaver(const char *outFileName, Crystal *crystal);
    void save(double time);
    void operator() (Carbon *carbon);

private:
    Crystal *_crystal;
    void separator();
};

#endif // CRYSTALSAVER_H
