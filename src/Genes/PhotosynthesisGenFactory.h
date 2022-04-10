#ifndef ARTIFICIALEVOLUTION2_PHOTOSYNTHESISGENFACTORY_H
#define ARTIFICIALEVOLUTION2_PHOTOSYNTHESISGENFACTORY_H

#include "GenFactory.h"

#include "../Cell.h"
#include "../vector2.h"
#include "../World.h"

class PhotosynthesisGenFactory : public GenFactory {
public:
    void addGenToGenome(Genome &genome) const override {
        // photosynthesis gen
        static gen_callback_T photosynthesis_function = [](const std::vector<double> &params, Cell &cell, World &world) -> int {
            const int NEXT_GEN = 0;

            cell.getCreature()->increaseEnergy(20);

            return (int) (params[NEXT_GEN] * 1000);
        };

        Gen photosynthesis_gen(
                Random::get().dv(1),
                photosynthesis_function,
                "Photosynthesis gen"
        );

        genome.addGen(photosynthesis_gen, 1);
    }
};

#endif //ARTIFICIALEVOLUTION2_PHOTOSYNTHESISGENFACTORY_H
