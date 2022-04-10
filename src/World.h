#ifndef ARTIFICIALEVOLUTION2_WORLD_H
#define ARTIFICIALEVOLUTION2_WORLD_H

#include "Cell.h"
#include "Creature.h"
#include "vector2.h"

#include <array>
#include <optional>

const int WORLD_SIZE = 80;

class World {
public:
    World(const World &world) : World(world.m_world_size) {
        for (int i = 0; i < m_world_size * m_world_size; ++i) {
            m_world[i] = world.m_world[i];
        }
    }

    explicit World(int world_size = 80) : m_world_size(world_size) {
        m_world = new Cell *[world_size * world_size];
    };

    bool isOutside(const vector2 &position) {
        return position.x < 0 || position.x >= m_world_size
               || position.y < 0 || position.y >= m_world_size;
    }

    bool move_cell(const vector2 &from, const vector2 &to) {
        if (!(*this)[from]) return false;
        if ((*this)[to]) return false;

        (*this)[to] = (*this)[from];
        (*this)[from] = nullptr;

        return true;
    }

    Cell *&operator[](const vector2 &position) {
        return m_world[get_index_by_position(position)];
    }

    const Cell *const &operator[](const vector2 &position) const {
        return m_world[get_index_by_position(position)];
    }

    [[nodiscard]] int getSize() const {
        return m_world_size;
    }

    void addCreature(Creature *creature) {
        m_creatures.push_back(creature);
    }

    void removeCreature(Creature *creature) {
        for (int i = 0; i < m_world_size * m_world_size; ++i) {
            if (!m_world[i]) continue;

            if (m_world[i]->getCreature() == creature) {
                delete m_world[i];
                m_world[i] = nullptr;
            }
        }

        for (auto itr = m_creatures.begin(); itr != m_creatures.end(); ++itr) {
            if (*itr == creature) {
                m_creatures.erase(itr);

                break;
            }
        }
    }

    std::vector<Creature *> &getCreatures() {
        return m_creatures;
    }

protected:
    [[nodiscard]] std::size_t get_index_by_position(const vector2 &position) const {
        return position.x * m_world_size + position.y;
    }

    Cell **m_world;
    std::vector<Creature *> m_creatures;
    const int m_world_size;
};

#endif //ARTIFICIALEVOLUTION2_WORLD_H
