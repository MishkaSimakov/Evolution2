#ifndef ARTIFICALEVOLUTION2_WORLD_H
#define ARTIFICALEVOLUTION2_WORLD_H

#include "Cell.h"
#include "vector2.h"

#include <array>
#include <optional>

const int WORLD_SIZE = 80;

class World {
public:
    explicit World(int world_size = 80) : m_world_size(world_size) {
        m_world = new Cell *[world_size * world_size];
    };

    ~World() {
        delete[] m_world;
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

protected:
    [[nodiscard]] std::size_t get_index_by_position(const vector2 &position) const {
        return position.x * m_world_size + position.y;
    }

    Cell **m_world;
    const int m_world_size;
};

#endif //ARTIFICALEVOLUTION2_WORLD_H
