#ifndef ARTIFICIALEVOLUTION2_SEPARATEGENFACTORY_H
#define ARTIFICIALEVOLUTION2_SEPARATEGENFACTORY_H

#include "GenFactory.h"

#include "../Cell.h"
#include "../vector2.h"
#include "../World.h"

class SeparateGenFactory : public GenFactory {
public:
    void addGenToGenome(Genome &genome) const override {
        // next gen for this cell (2 genes: success and failure), next gen for new cell, direction for growth, mutate or not
        static gen_callback_T separate_growth_function = [](const std::vector<double> &params, Cell &cell, World &world) -> int {
            const int DIRECTION_GEN = 0;
            const int SUCCESS_NEXT_GEN = 1;
            const int FAILURE_NEXT_GEN = 2;
            const int GROWN_GEN = 3;
            const int MUTATION_GEN = 4;

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

            auto new_creature = Creature::inherit(*cell.getCreature(), 0.01);

            world.addCreature(new_creature);

            Cell *new_cell = world[new_cell_position] = new Cell(new_cell_position, new_creature);

            new_cell->setActiveGen((int) (params[GROWN_GEN] * 1000));

            new_creature->setEnergy(std::min(75, cell.getCreature()->getEnergy()));
            cell.getCreature()->increaseEnergy(-125);

            return (int) (params[SUCCESS_NEXT_GEN] * 1000);
        };

        Gen separate_gen(
                Random::get().dv(5),
                separate_growth_function,
                "Separate gen"
        );

        genome.addGen(separate_gen, 4);
    }
};

#endif //ARTIFICIALEVOLUTION2_SEPARATEGENFACTORY_H
