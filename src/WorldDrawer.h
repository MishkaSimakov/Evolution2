#ifndef ARTIFICIALEVOLUTION2_WORLDDRAWER_H
#define ARTIFICIALEVOLUTION2_WORLDDRAWER_H

#include "Cell.h"
#include "World.h"
#include "Statistics.h"

#include <SFML/Graphics.hpp>
#include <map>

class WorldDrawer {
public:
    explicit WorldDrawer(int window_width = 1200, int window_height = 800, int cell_size = 10) :
            m_cell_size((float) cell_size, (float) cell_size) {
        sf::VideoMode mode(window_width, window_height);
        m_window.create(mode, "Artificial evolution");

        m_view = m_window.getDefaultView();
        m_window.setView(m_view);
    }

    void close() {
        m_window.close();
    }

    bool isOpen() const {
        return m_window.isOpen();
    }

    vector2 getHoveredCellPosition() const {
        auto mouse_position = sf::Mouse::getPosition(m_window);

        float x_position = ((float) mouse_position.x - m_info_panel_width) / m_cell_size.x;
        float y_position = (float) mouse_position.y / m_cell_size.y;

        return {(int) x_position, (int) y_position};
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
                    if (m_callbacks.count(event.type)) {
                        m_callbacks[event.type](event);
                    }

                    break;
            }
        }

        if (m_is_visible) {
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
    }

    void setCallback(sf::Event::EventType event_type, const std::function<void(const sf::Event &)> &callback) {
        m_callbacks[event_type] = callback;
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
                        m_info_panel_width + (float) x * m_cell_size.x,
                        (float) y * m_cell_size.y
                );
                rect.setSize(m_cell_size);

                rect.setFillColor(world[{x, y}]->getCreature()->getColor());

                m_window.draw(rect);
            }
        }
    }

    void draw(Genome &genome) {
        std::cout << std::endl;
        std::cout << "Cell genome: " << std::endl;

        for (auto &gen : genome.getGenes()) {
            std::cout << "Name: " << gen.name << std::endl;
            std::cout << "Parameters: ";

            for (auto &param : gen.params) {
                std::cout << param << " (" << (int) (param * 1000) % (genome.getGenes().size()) << ") ";
            }

            std::cout << std::endl;
        }
    }

    void draw(Statistics &statistics) {
        sf::RectangleShape delimiter;

        delimiter.setFillColor(sf::Color::Black);
        delimiter.setPosition(m_info_panel_width - 5.f, 0);
        delimiter.setSize({5.f, (float) m_window.getSize().y});

        m_window.draw(delimiter);


        sf::Font font;

        font.loadFromFile("fonts/arial.ttf");

        sf::Text generation_text;
        generation_text.setString(L"Поколение: " + std::to_wstring(statistics.records.back().generation));
        generation_text.setFillColor(sf::Color::Black);
        generation_text.setCharacterSize(30);
        generation_text.setPosition(10, 10);
        generation_text.setFont(font);

        m_window.draw(generation_text);

        sf::Text cells_count_text;
        cells_count_text.setString(L"Количество клеток: " + std::to_wstring(statistics.records.back().cells_count));
        cells_count_text.setFillColor(sf::Color::Black);
        cells_count_text.setCharacterSize(30);
        cells_count_text.setPosition(10, 50);
        cells_count_text.setFont(font);

        m_window.draw(cells_count_text);
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

    float m_info_panel_width{400.f};

    bool m_is_visible{true};

    std::map<sf::Event::EventType, std::function<void(const sf::Event &)>> m_callbacks;
};

#endif //ARTIFICIALEVOLUTION2_WORLDDRAWER_H
