#ifndef ARTIFICIALEVOLUTION2_EATCELLGENFACTORY_H
#define ARTIFICIALEVOLUTION2_EATCELLGENFACTORY_H

#include "GenFactory.h"

#include "../Cell.h"
#include "../vector2.h"
#include "../World.h"

class EatCellGenFactory : public GenFactory {
public:
    void addGenToGenome(Genome &genome) const override {
        // photosynthesis gen
        static gen_callback_T eat_function = [](const std::vector<double> &params, Cell &cell, World &world) -> int {
            const int SUCCESS_NEXT_GEN = 0;
            const int FAILURE_NEXT_GEN = 1;
            const int DIRECTION_GEN = 2;

            int direction = std::floor(params[DIRECTION_GEN] * 4 - 0.0001);

            const std::array<vector2, 4> directions{
                    (vector2) {1, 0},
                    (vector2) {0, 1},
                    (vector2) {-1, 0},
                    (vector2) {0, -1}
            };

            vector2 bite_position = cell.getPosition() + directions[direction];
            if (world.isOutside(bite_position) || !world[bite_position] || world[bite_position]->getCreature() == cell.getCreature()) {
                cell.getCreature()->increaseEnergy(-5);

                return (int) (params[FAILURE_NEXT_GEN] * 1000);
            }

            world[bite_position]->getCreature()->increaseEnergy(-15);
            cell.getCreature()->increaseEnergy(15);

            return (int) (params[SUCCESS_NEXT_GEN] * 1000);
        };

        Gen eat_gen(
                Random::get().dv(3),
                eat_function,
                "Eat cell gen"
        );

        genome.addGen(eat_gen, 4);
    }
};

#endif //ARTIFICIALEVOLUTION2_EATCELLGENFACTORY_H
