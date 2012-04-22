#include "dualreaction.h"

DualReaction::DualReaction(Surface *surface): DualReaction::Reaction(surface) {}

double DualReaction::commonRate() {
    return coef() * _sites.size() / (2*_surface->numberOfSites());
}

void DualReaction::reset() {
    _sites.clear();
}
