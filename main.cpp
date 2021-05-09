#include <SFML/Graphics.hpp>

#include <iostream>
#include <chrono>
#include <random>
#include <thread>


auto generator = std::default_random_engine(std::random_device()());
std::uniform_int_distribution<int> distribution(0, 700);

class Vis {

    public:

        Vis() {
            screen = std::make_unique<sf::RenderWindow>(sf::VideoMode(1600, 1000), "");

            font.loadFromFile("font.ttf");

            textGenerate.setFont(font);
            textGenerate.setCharacterSize(15);
            textGenerate.setPosition(25.f, 70.f);
            textGenerate.setFillColor(sf::Color::White);
            textGenerate.setString("Generate  New  Array");

            sorting.setFont(font);
            sorting.setCharacterSize(15);
            sorting.setPosition(1480.f, 70.f);
            sorting.setFillColor(sf::Color::White);
            sorting.setString("Sort !");

            for (auto i = 0; i < 200; i++) {
                vec.push_back(std::make_unique<sf::RectangleShape>());
            }

            textureBackground.loadFromFile("pas.png");
            background.setTexture(textureBackground);
            background.setScale(1, 0.1);
            background.setPosition(0.f, -115.f);


            auto move = 0.f;
            for (auto& rec : vec) {
                rec->setSize({5.f, distribution(generator)});
                rec->setPosition({150.f + move, 150.f});
                rec->setScale(0.9, 0.9);
                rec->setFillColor(sf::Color(102, 153, 255));
                move += 6.f;
            }
        }

        void run() {
            sf::Clock clock;
            sf::Time timeSinceLastUpdate = sf::Time::Zero;
            while (screen->isOpen()) {
                processEvents();
                timeSinceLastUpdate += clock.restart();
                while (timeSinceLastUpdate > TimePerFrame) {
                    timeSinceLastUpdate -= TimePerFrame;
                    processEvents();
                    update(TimePerFrame);

                }
                render();
            }
        }

    private:

        void processEvents() {
            sf::Event event;
            while (screen->pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::MouseButtonPressed:
                        handlePlayerInput(event.mouseButton.button, true);
                        break;
                    case sf::Event::Closed:
                        screen->close();
                        break;
                }
            }
        }

        void handlePlayerInput(sf::Mouse::Button key, bool pressed) {
            sf::Vector2i position = sf::Mouse::getPosition(*screen);
            sf::Vector2f mousePosition = screen->mapPixelToCoords(position);
            if (sorted && mousePosition.y >= 70.f && mousePosition.y <= 100.f) {
                if (mousePosition.x >= 25.f && mousePosition.x <= 200.f &&
                    key == sf::Mouse::Left) {
                    for (auto& rec : vec) {
                        rec->setSize({5.f, distribution(generator)});
                        rec->setFillColor(sf::Color(102, 153, 255));
                    }
                } else if (sorted && mousePosition.x >= 1480.f && mousePosition.x <= 1580.f) {
                    /* start sorting the array */
                    sorted = false;
                    sorting.setColor(sf::Color::Red);
                    textGenerate.setColor(sf::Color::Red);
                }
            }
            if (sorted) {
                left = 0;
                i = 0;
                j = 0;
            }
        }

        void update(sf::Time deltaTime) {
            sf::Vector2i position = sf::Mouse::getPosition(*screen);
            sf::Vector2f mousePosition = screen->mapPixelToCoords(position);
            if (sorted && mousePosition.y >= 70.f && mousePosition.y <= 100.f &&
                mousePosition.x >= 25.f && mousePosition.x <= 200.f) {
                cursor.loadFromSystem(sf::Cursor::Hand);
                textGenerate.setColor(sf::Color(155, 155, 161));
            } else if (sorted && mousePosition.y >= 70.f && mousePosition.y <= 100.f &&
                mousePosition.x >= 1480.f && mousePosition.x <= 1530.f) {
                cursor.loadFromSystem(sf::Cursor::Hand);
                sorting.setColor(sf::Color(155, 155, 161));
            } else if (sorted) {
                cursor.loadFromSystem(sf::Cursor::Arrow);
                sorting.setColor(sf::Color::White);
                textGenerate.setColor(sf::Color::White);
            } else {
                cursor.loadFromSystem(sf::Cursor::Arrow);
            }
            screen->setMouseCursor(cursor);
        }

        void render() {
            screen->clear(sf::Color::White);

            if (!sorted && i >= vec.size() - 1 && j >= vec.size() - 1) {
                sorted = true;
                for (auto& rec : vec) {
                    rec->setFillColor(sf::Color::Green);
                }
            }
            if (!sorted) {
                for (auto k = 0; k < vec.size() - left; k++) {
                    vec[k]->setFillColor(sf::Color(102, 153, 255));
                }
            }
            if (!sorted) {
                vec[j]->setFillColor(sf::Color::Red);                vec[j + 1]->setFillColor(sf::Color::Red);
                if (vec[j + 1]->getSize().y < vec[j]->getSize().y) {
                    auto temp = vec[j]->getSize().y;
                    vec[j]->setSize({5.f, vec[j + 1]->getSize().y});
                    vec[j + 1]->setSize({5.f, temp});
                    vec[j]->setFillColor(sf::Color::Green);                    vec[j + 1]->setFillColor(sf::Color::Green);
                }
                j++;
                if (j == vec.size() - left - 1) {
                    for (auto k = vec.size() - left - 1; k < vec.size(); k++) {
                        vec[k]->setFillColor(sf::Color(204, 153, 255));
                    }
                    j = 0;
                    i++;
                    left++;
                }
            }

            using namespace std::literals;
            std::this_thread::sleep_for(0.0000001ms);

            for (auto& rec : vec) {
                screen->draw(*rec);
            }
            screen->draw(background);
            screen->draw(textGenerate);
            screen->draw(sorting);
            screen->display();
        }


        std::unique_ptr<sf::RenderWindow> screen;
        sf::Time TimePerFrame = sf::seconds(1.f / 10.f);
        std::vector<std::unique_ptr<sf::RectangleShape>> vec;
        sf::Sprite background;
        sf::Texture textureBackground;
        sf::Font font;
        sf::Text textGenerate, sorting;
        sf::Cursor cursor;
        bool sorted = true;
        bool isPressed = false;
        bool was = false;
        int i = 0;
        int j = 0;
        int left = 0;
};


int main() {
    Vis v;
    v.run();
}
