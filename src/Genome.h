#ifndef ARTIFICIALEVOLUTION2_GENOME_H
#define ARTIFICIALEVOLUTION2_GENOME_H

#include "Random.h"

#include <array>
#include <utility>
#include <vector>
#include <functional>

class Cell;

class World;


using gen_callback_T = std::function<int(const std::vector<double> &, Cell &cell, World &world)>;

/**
 * Каждый ген имеет свой размер. Если у клетки номер активного гена попадает в диапазон данного гена, то вызывается
 * лямбда-функция этого гена. За размер отвечает параметр size. Все числа, указанные в векторе params будут меняться
 * при наследовании в диапазоне от 0. до 1.
 * В лямбда функцию передаётся номер вызванного гена, клетка, вызвавшая его, а также мир симуляции. Лямбда-функция меняет
 * характеристики клетки и мира, а затем возвращает номер следующего активного гена, который будет у клетки.
 */
struct Gen {
    Gen(std::vector<double> p, const gen_callback_T &c, std::string n) :
            params(std::move(p)),
            callback(c),
            name(std::move(n)) {};

    std::string name;
    std::vector<double> params;
    const gen_callback_T &callback;
};

class Genome {
public:
    Genome() = default;

    static Genome inherit(const Genome &parent, double mutation_probability = 0.1) {
        Genome genome;
        genome.m_genome.reserve(parent.m_genome.size());

        for (const auto &parent_gen: parent.m_genome) {
            auto &new_gen = genome.m_genome.emplace_back(
                    parent_gen.params,
                    parent_gen.callback,
                    parent_gen.name
            );

            for (auto &param: new_gen.params) {
                if (Random::get().b(mutation_probability))
                    param = Random::get().d();
            }
        }

        return genome;
    }

    void addGen(Gen &gen, int count = 1) {
        m_genome.reserve(count);

        for (int i = 0; i < count; ++i) {
            m_genome.push_back(gen);
        }
    }

    Gen &getGen(int gen_id) {
        return m_genome[gen_id % m_genome.size()];
    }

    [[nodiscard]] const std::vector<Gen> &getGenes() const {
        return m_genome;
    }

protected:
    std::vector<Gen> m_genome;
};

#endif //ARTIFICIALEVOLUTION2_GENOME_H
