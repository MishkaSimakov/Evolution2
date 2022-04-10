#ifndef ARTIFICIALEVOLUTION2_GENOMEFACTORY_H
#define ARTIFICIALEVOLUTION2_GENOMEFACTORY_H

#include "GrowthGenFactory.h"
#include "PhotosynthesisGenFactory.h"
#include "SeparateGenFactory.h"
#include "EatCellGenFactory.h"

#include <array>

class GenomeFactory {
public:
    void addGenesToGenome(Genome &genome) const {
        for (auto &gen : genes) {
            gen->addGenToGenome(genome);
        }
    }
protected:
    const std::vector<GenFactory *> genes{
            new GrowthGenFactory,
            new PhotosynthesisGenFactory,
            new SeparateGenFactory,
            new EatCellGenFactory
    };
};

#endif //ARTIFICIALEVOLUTION2_GENOMEFACTORY_H
