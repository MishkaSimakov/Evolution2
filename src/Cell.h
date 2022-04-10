#ifndef ARTIFICIALEVOLUTION2_CELL_H
#define ARTIFICIALEVOLUTION2_CELL_H

#include "vector2.h"
#include "Genome.h"
#include "Creature.h"

#include <iostream>

class Cell {
public:
    Cell() = default;

    Cell(const vector2 &position, Creature *creature) : m_position(position), m_creature(creature) {};

    [[nodiscard]] vector2 &getPosition() {
        return m_position;
    }

    void setPosition(const vector2 &position) {
        m_position = position;
    }

    Genome &getGenome() {
        return m_creature->getGenome();
    }

    Creature *getCreature() {
        return m_creature;
    }

    void setCreature(Creature *creature) {
        m_creature = creature;
    }

    void setActiveGen(int gen_id) {
        m_active_gen = gen_id;
    }

    [[nodiscard]] int getActiveGen() const {
        return m_active_gen;
    }

protected:
    vector2 m_position;
    int m_active_gen{0};

    Creature *m_creature{nullptr};
};

#endif //ARTIFICIALEVOLUTION2_CELL_H
