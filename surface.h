#ifndef SURFACE_H
#define SURFACE_H

#include <map>
#include <set>
#include "crystal.h"

#include <random>

class Reaction;

class Surface
{
public:
    Surface(Crystal *crystal);

    void operator() (Carbon *carbon);

    int numberOfSites();

    void addHydrogen(Carbon *carbon);
    void removeHydrogen(Carbon *carbon);

    void addCarbon(Carbon *carbon, Carbon *bottomFirst, Carbon *bottomSecond);
    void removeCarbon(Carbon *carbon, Carbon *bottomFirst, Carbon *bottomSecond);
    void moveCarbon(Carbon *carbon, const int3 &to,
                    const std::pair<Carbon *, Carbon *> &fromBasis,
                    const std::pair<Carbon *, Carbon *> &toBasis);

    void addDimer(Carbon *first, Carbon *second);
    void dropDimer(Carbon *first);

private:
    void init();

    Crystal *_crystal;
    Reaction **_reactions;
    std::set<Carbon *> _activeCarbons, _hydroCarbons;
    std::map<Carbon *,Carbon *> _dimerBonds;
};

#endif // surface_H