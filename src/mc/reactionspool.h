#ifndef REACTIONSPOOL_H
#define REACTIONSPOOL_H

#include <deque>
#include <vector>
#include <string>

#include "../reactions/abshreaction.h"
#include "../reactions/addch2reaction.h"
#include "../reactions/addhreaction.h"
#include "../reactions/formdimerreaction.h"
#include "../reactions/dropdimerreaction.h"
#include "../reactions/etchingreaction.h"
#include "../reactions/migrationhreaction.h"
#include "../reactions/migrationbridgereaction.h"
#include "../reactions/migrationfrontdown.h"

class ReactionsPool
{
public:
    ReactionsPool(Surface *surface, Crystal *crystal);

    std::deque<std::string> reactionsNames() const;
    std::deque<int> reactionsTimes() const;

    void seeAtActives(const std::set<Carbon *> &activeCarbons);
    void seeAtHydrogens(const std::set<Carbon *> &hydroCarbons);
    void seeAtDimer(const std::map<Carbon *, Carbon *> &dimers);

    double doReaction();
    void reset();

    FormDimerReaction &formDimerReaction();

private:
    double totalRate();

    AbsHReaction _absH;
    AddHReaction _addH;
    FormDimerReaction _formDimer;
    DropDimerReaction _dropDimer;
    AddCH2Reaction _addCH2;
    EtchingReaction _etching;
    MigrationHReaction _migrationH;
    MigrationBridgeReaction _migrationBridge;
    MigrationFrontDown _migrationFrontDown;

    std::vector<Reaction *> _reactions;

    Surface *_surface;

};

#endif // REACTIONSPOOL_H
