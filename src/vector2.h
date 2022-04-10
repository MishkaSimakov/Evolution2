#ifndef ARTIFICIALEVOLUTION2_VECTOR2_H
#define ARTIFICIALEVOLUTION2_VECTOR2_H

struct vector2 {
    int x{}, y{};

    vector2() = default;

    vector2(int _x, int _y) : x(_x), y(_y) {};

    bool operator<(const vector2 &other) const {
        if (x < other.x) return true;
        if (x == other.x) return y < other.y;

        return false;
    }

    vector2 operator+(const vector2 &other) const {
        return {x + other.x, y + other.y};
    }

    void operator+=(const vector2 &other) {
        x += other.x;
        y += other.y;
    }

    vector2 operator*(int scalar) const {
        return {x * scalar, y * scalar};
    }

    bool operator==(const vector2 &other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const vector2 &other) const {
        return x != other.x || y != other.y;
    }

    vector2 operator-(const vector2 &other) {
        return {x - other.x, y - other.y};
    }

    vector2 operator-() {
        x = -x;
        y = -y;

        return *this;
    }
};

#endif //ARTIFICIALEVOLUTION2_VECTOR2_H
