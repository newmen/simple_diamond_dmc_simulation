#ifndef RUNNER_H
#define RUNNER_H

#include <vector>

#include "configurator.h"
#include "handbook.h"

#include "../reactions/reactor.h"
#include "../reactions/reaction.h"
#include "../surface/surface.h"
#include "../savers/saver.h"
#include "../savers/reactionpoolsaver.h"
#include "../savers/surfacesaver.h"
#include "../savers/crystalsaver.h"

class Runner
{
public:
    Runner(const Configurator &configurator);
    ~Runner();

    void run();

private:
    void save();

    const Configurator &_configurator;
    Handbook _handbook;

    double _totalTime;
    Crystal *_crystal;
    Surface *_surface;
    Reactor *_reactor;
    ReactionsPool *_reactionsPool;
    std::vector<Saver *> _savers;
};

#endif // RUNNER_H
