#include "World.h"
#include "Genome.h"
#include "WorldDrawer.h"

#include "Genes/GenomeFactory.h"


int main() {
    World world;
    WorldDrawer drawer;
    Statistics statistics;

    Genome base_genome;
    GenomeFactory().addGenesToGenome(base_genome);

    auto *adam = new Creature;
    adam->setColor({128, 128, 128});
    adam->setGenome(base_genome);

    int generation_id = 0;

    Cell *hovered_cell{nullptr};

    drawer.setCallback(sf::Event::MouseButtonPressed, [&](const sf::Event &event) {
        vector2 pos = drawer.getHoveredCellPosition();

        hovered_cell = world[pos];
    });

    while (drawer.isOpen()) {
        if (world.getCreatures().empty()) {
            generation_id = 0;

            adam = Creature::inherit(*adam);
            adam->setEnergy(10000);


            world.addCreature(adam);

            world[{40, 40}] = new Cell();
            world[{40, 40}]->setPosition({40, 40});
            world[{40, 40}]->setCreature(adam);
        }

        //for each creature
        for (auto creature: world.getCreatures()) {
            creature->incrementAge();

            if (creature->getEnergy() <= 0 || creature->getAge() > 250) {
                world.removeCreature(creature);
            }
        }

        int cells_count = 0;
        auto old_world = world;
        for (int x = 0; x < old_world.getSize(); ++x) {
            for (int y = 0; y < old_world.getSize(); ++y) {
                if (!old_world[{x, y}]) continue;

                auto cell = old_world[{x, y}];

                cell->setActiveGen(
                        cell->getGenome().getGen(cell->getActiveGen()).callback(
                                cell->getGenome().getGen(cell->getActiveGen()).params,
                                *cell,
                                world
                        )
                );

                cell->getCreature()->increaseEnergy(-1);

                ++cells_count;
            }
        }

        statistics.records.push_back(
                {
                        generation_id,
                        cells_count,
                        (int) world.getCreatures().size()
                }
        );

        drawer.pollEvents();

        if (drawer.isVisible()) {
            drawer.startDraw();

            drawer.draw(world);
            drawer.draw(statistics);

            if (hovered_cell) {
                drawer.draw(hovered_cell->getGenome());
                hovered_cell = nullptr;
            }

            drawer.endDraw();
        }

        ++generation_id;
    }

    return 0;
}
