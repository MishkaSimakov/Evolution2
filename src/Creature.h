#ifndef ARTIFICIALEVOLUTION2_CREATURE_H
#define ARTIFICIALEVOLUTION2_CREATURE_H

#include "Genome.h"

#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include <set>

class Cell;

class Creature {
public:
    Creature() = default;

    static Creature *inherit(Creature &parent, double mutation_probability = 0.1) {
        auto new_creature = new Creature;
        new_creature->setGenome(Genome::inherit(parent.getGenome(), mutation_probability));
        new_creature->setColor(
                sf::Color(
                        std::clamp(parent.getColor().r + Random::get().i(11) - 5, 0, 255),
                        std::clamp(parent.getColor().g + Random::get().i(11) - 5, 0, 255),
                        std::clamp(parent.getColor().b + Random::get().i(11) - 5, 0, 255)
                )
        );

        return new_creature;
    }

    Genome &getGenome() {
        return m_genome;
    }

    void setGenome(Genome genome) {
        m_genome = std::move(genome);
    }

    void setColor(sf::Color color) {
        m_color = color;
    }

    [[nodiscard]] const sf::Color &getColor() const {
        return m_color;
    }

    [[nodiscard]] int getEnergy() const {
        return m_energy;
    }

    void setEnergy(int energy) {
        m_energy = energy;
    }

    void increaseEnergy(int delta) {
        m_energy += delta;
    }

    void incrementAge() {
        ++m_age;
    }

    [[nodiscard]] int getAge() const {
        return m_age;
    }

protected:
    sf::Color m_color;
    Genome m_genome;
    int m_energy{};
    int m_age{0};
};

#endif //ARTIFICIALEVOLUTION2_CREATURE_H
