#ifndef ARTIFICIALEVOLUTION2_STATISTICS_H
#define ARTIFICIALEVOLUTION2_STATISTICS_H

#include <vector>

struct Statistics {
    struct Record {
        int generation;
        int cells_count;
        int creatures_count;
    };

    std::vector<Record> records;
};

#endif //ARTIFICIALEVOLUTION2_STATISTICS_H
