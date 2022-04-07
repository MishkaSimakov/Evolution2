#ifndef ARTIFICALEVOLUTION2_WORLDDRAWER_H
#define ARTIFICALEVOLUTION2_WORLDDRAWER_H

#ifndef EVOLUTION_WINDOW_H
#define EVOLUTION_WINDOW_H

#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "World.h"

class WorldDrawer {
public:
    explicit WorldDrawer(int window_width = 800, int window_height = 800, int cell_size = 10) :
            m_cell_size((float) cell_size, (float) cell_size) {
        sf::VideoMode mode(window_width, window_height);
        m_window.create(mode, "Artificial evolution");

        m_view = m_window.getDefaultView();
        m_view.setRotation(180);

        m_window.setView(m_view);
    }

    void close() {
        m_window.close();
    }

    bool isOpen() const {
        return m_window.isOpen();
    }

    void pollEvents() {
        sf::Event event;

        while (m_window.pollEvent(event)) {
            switch (event.type) {
                case (sf::Event::Closed):
                    close();
                    break;
                case (sf::Event::KeyPressed):
                    if (event.key.code == sf::Keyboard::Space)
                        m_is_visible = !m_is_visible;
                default:
                    break;
            }
        }

        const float MOVEMENT_SPEED = 0.1f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            m_offset.x += MOVEMENT_SPEED;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            m_offset.x -= MOVEMENT_SPEED;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            m_offset.y -= MOVEMENT_SPEED;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            m_offset.y += MOVEMENT_SPEED;

        updateView();
    }

    void startDraw() {
        m_window.clear(sf::Color::White);
    }

    void draw(World &world) {
        for (int x = 0; x < world.getSize(); x++) {
            for (int y = 0; y < world.getSize(); y++) {
                if (!world[{x, y}]) continue;

                sf::RectangleShape rect;
                rect.setPosition(
                        (float) x * m_cell_size.x,
                        (float) y * m_cell_size.y
                );
                rect.setSize(m_cell_size);

                rect.setFillColor(sf::Color::Red);

                m_window.draw(rect);
            }
        }
    }

    void endDraw() {
        m_window.display();
    }

    bool isVisible() const {
        return m_is_visible;
    }

protected:
    void updateView() {
        m_view.setCenter(m_window.getDefaultView().getCenter() + m_offset);

        m_window.setView(m_view);
    }

    sf::RenderWindow m_window;
    sf::View m_view;

    const sf::Vector2f m_cell_size;

    sf::Vector2f m_offset{0, 0};

    bool m_is_visible{true};
};

#endif //EVOLUTION_WINDOW_H

#endif //ARTIFICALEVOLUTION2_WORLDDRAWER_H
