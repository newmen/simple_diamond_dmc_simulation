#ifndef ADDCH2REACTION_H
#define ADDCH2REACTION_H

#include "../surface/crystal.h"
#include "dualreaction.h"

class AddCH2Reaction : public DualReaction
{
public:
    AddCH2Reaction(Surface *surface, Crystal *crystal);

    void seeAt(Carbon *first, Carbon *second);
    void doIt();
    void reset();

protected:
    double coef() const;

private:
    Crystal *_crystal;
    std::vector<int3> _positions;
};

#endif // ADDCH2REACTION_H
