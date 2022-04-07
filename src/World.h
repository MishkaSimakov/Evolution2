#ifndef ARTIFICALEVOLUTION2_WORLD_H
#define ARTIFICALEVOLUTION2_WORLD_H

#include "Cell.h"
#include "vector2.h"

#include <array>
#include <optional>

template<std::size_t map_size>
class World {
public:
    World() = default;

    bool move_cell(const vector2 &from, const vector2 &to) {
        if (!(*this)[from]) return false;
        if ((*this)[to]) return false;

        (*this)[to] = (*this)[from];
        (*this)[from] = nullptr;
    }

    Cell *operator[](const vector2 &position) {
        return m_world[get_index_by_position(position)];
    }

    const Cell *operator[](const vector2 &position) const {
        return m_world[get_index_by_position(position)];
    }

protected:
    std::size_t get_index_by_position(const vector2 &position) {
        return position.x * map_size + position.y;
    }

    std::array<Cell *, map_size * map_size> m_world{nullptr};
};

#endif //ARTIFICALEVOLUTION2_WORLD_H
