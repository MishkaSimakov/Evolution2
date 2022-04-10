#ifndef ARTIFICIALEVOLUTION2_GENFACTORY_H
#define ARTIFICIALEVOLUTION2_GENFACTORY_H

#include "../Genome.h"

class GenFactory {
public:
    virtual void addGenToGenome(Genome &genome) const = 0;
};

#endif //ARTIFICIALEVOLUTION2_GENFACTORY_H
