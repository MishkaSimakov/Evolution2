#include "World.h"
#include "WorldDrawer.h"

#include <iostream>

int main() {
    World world;

    world[{1, 1}] = new Cell;

    WorldDrawer drawer;

    while (drawer.isOpen()) {
        drawer.pollEvents();

        drawer.startDraw();
        drawer.draw(world);
        drawer.endDraw();
    }

    return 0;
}
