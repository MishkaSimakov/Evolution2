#ifndef ARTIFICIALEVOLUTION2_GROWTHGENFACTORY_H
#define ARTIFICIALEVOLUTION2_GROWTHGENFACTORY_H

#include "GenFactory.h"

#include "../Cell.h"
#include "../vector2.h"
#include "../World.h"

class GrowthGenFactory : public GenFactory {
public:
    void addGenToGenome(Genome &genome) const override {
        // next gen for this cell (2 genes: success and failure), next gen for new cell, direction for growth
        static gen_callback_T function = [](const std::vector<double> &params, Cell &cell, World &world) -> int {
            const int DIRECTION_GEN = 0;
            const int SUCCESS_NEXT_GEN = 1;
            const int FAILURE_NEXT_GEN = 2;
            const int GROWN_GEN = 3;

            int direction = std::floor(params[DIRECTION_GEN] * 4 - 0.0001);

            const std::array<vector2, 4> directions{
                    (vector2) {1, 0},
                    (vector2) {0, 1},
                    (vector2) {-1, 0},
                    (vector2) {0, -1}
            };

            vector2 new_cell_position = cell.getPosition() + directions[direction];

            if (world[new_cell_position] || world.isOutside(new_cell_position))
                return (int) (params[FAILURE_NEXT_GEN] * 1000);

            Cell *new_cell = world[new_cell_position] = new Cell(new_cell_position, cell.getCreature());

            new_cell->setActiveGen((int) (params[GROWN_GEN] * 1000));

            cell.getCreature()->increaseEnergy(-100);

            return (int) (params[SUCCESS_NEXT_GEN] * 1000);
        };

        Gen growth_gen(
                Random::get().dv(4),
                function,
                "Growth gen"
        );

        genome.addGen(growth_gen, 4);
    }
};

#endif //ARTIFICIALEVOLUTION2_GROWTHGENFACTORY_H
