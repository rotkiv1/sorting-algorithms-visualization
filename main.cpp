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

            s.setPosition(410.f, 73.5);
            s.setFillColor(sf::Color::Black);
            s.setSize({0.f, 0.f});

            sizeOfArray.setFont(font);
            sizeOfArray.setCharacterSize(16.f);
            sizeOfArray.setFillColor(sf::Color::Black);
            sizeOfArray.setPosition(newArray.getLocalBounds().width + 408.f, 71.f);

            textGenerate.setFont(font);
            textGenerate.setCharacterSize(15);
            textGenerate.setPosition(25.f, 70.f);
            textGenerate.setFillColor(sf::Color::White);
            textGenerate.setString("Generate  New  Array");

            newArray.setFont(font);
            newArray.setCharacterSize(15);
            newArray.setPosition(250.f, 70.f);
            newArray.setFillColor(sf::Color::White);
            newArray.setString("Change  array  size  ");

            sorting.setFont(font);
            sorting.setCharacterSize(15);
            sorting.setPosition(1480.f, 70.f);
            sorting.setFillColor(sf::Color::White);
            sorting.setString("Sort");

            s1.setFillColor(sf::Color::Black);
            s1.setSize({9.f, 100.f});
            s1.setPosition((textGenerate.getLocalBounds().width + 270.f) / 2, 0.f);

            range.setFont(font);
            range.setCharacterSize(15);
            range.setFillColor(sf::Color::White);
            range.setString("[100, 399]");
            range.setPosition(newArray.getLocalBounds().width + 270, 90.f);

            moving.setFillColor(sf::Color::White);
            moving.setSize({80.f, 16.f});
            moving.setPosition(newArray.getLocalBounds().width + 260.f, 73.f);

            textureBackground.loadFromFile("pas.png");
            background.setTexture(textureBackground);
            background.setScale(1, 0.1);
            background.setPosition(0.f, -115.f);
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
                    case sf::Event::MouseButtonReleased:
                        handlePlayerInput(event.mouseButton.button, false);
                        break;
                    case sf::Event::TextEntered:
                        handleInput(event.key.code);
                        break;
                    case sf::Event::Closed:
                        screen->close();
                        break;
                }
            }
        }

        void handleInput(sf::Keyboard::Key name) {
            if (isClicked) {
                if (name == 8) {
                    if (!size.empty()) {
                        size.pop_back();
                        passed = true;
                    }
                } else {
                    auto curr = static_cast<char>(name);
                    if (curr >= '0' && curr <= '9') {
                        size += curr;
                        passed = true;
                        if (size.size() >= 2 && std::stoi(size) >= 400) {
                            passed = false;
                            size.pop_back();
                        }
                    } else {
                        passed = false;
                    }
                }
                if (passed) {
                    sizeOfArray.setString(size);
                    s.setPosition(sizeOfArray.getLocalBounds().width + 410, 73.5);
                    std::vector<std::unique_ptr<sf::RectangleShape>> temp;
                    auto determine = (size.empty()) ? 0 : std::stoi(size);
                    for (auto i = 0; i < determine; i++) {
                        temp.push_back(std::make_unique<sf::RectangleShape>());
                    }
                    auto moveDistance = 9.f;
                    auto recSize = 8.f;
                    auto move = 0.f;
                    if (determine > 175 && determine < 220) {
                        recSize = 6.f;
                        moveDistance = 7.f;
                    } else if (determine >= 220 && determine < 260) {
                        recSize = 5.f;
                        moveDistance = 6.f;
                    } else if (determine >= 260 && determine < 300) {
                        recSize = 4.f;
                        moveDistance = 5.f;
                    } else if (determine >= 300 && determine < 340) {
                        recSize = 3.5;
                        moveDistance = 4.5;
                    } else if (determine >= 340 && determine < 400) {
                        recSize = 2.5;
                        moveDistance = 3.5;
                    }
                    for (auto& rec : temp) {
                        rec->setSize({recSize, distribution(generator)});
                        rec->setPosition({800.f - determine * moveDistance / 2 + move, 150.f});
                        rec->setScale(0.9, 0.9);
                        rec->setFillColor(sf::Color(102, 153, 255));
                        move += moveDistance;
                    }
                    vec = std::move(temp);
                }
            } else {
                s.setSize({0.f, 0.f});
            }
        }

        void handlePlayerInput(sf::Mouse::Button key, bool pressed) {
            sf::Vector2i position = sf::Mouse::getPosition(*screen);
            sf::Vector2f mousePosition = screen->mapPixelToCoords(position);
            if (sorted && mousePosition.y >= 70.f && mousePosition.y <= 100.f &&
                mousePosition.x >= newArray.getLocalBounds().width + 260.f &&
                mousePosition.x <= newArray.getLocalBounds().width + 360.f) {
                isClicked = true;
                s.setSize({1.5, 14.f});
            } else {
                s.setSize({0.f, 0.f});
                isClicked = false;
            }
            if (sorted && mousePosition.y >= 70.f && mousePosition.y <= 100.f) {
                if (mousePosition.x >= 25.f && mousePosition.x <= 200.f &&
                    key == sf::Mouse::Left && pressed) {
                    for (auto& rec : vec) {
                        rec->setSize({8.f, distribution(generator)});
                        rec->setFillColor(sf::Color(102, 153, 255));
                    }
                } else if (sorted && mousePosition.x >= 1480.f && mousePosition.x <= 1580.f) {
                    /* start sorting the array */
                    sorted = false;
                    bubbleSort = true;
                    sorting.setColor(sf::Color::Red);
                    textGenerate.setColor(sf::Color::Red);
                    sizeOfArray.setColor(sf::Color::Red);
                    cursor.loadFromSystem(sf::Cursor::Arrow);
                    screen->setMouseCursor(cursor);
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
                textGenerate.setColor(sf::Color(155, 155, 161));
                cursor.loadFromSystem(sf::Cursor::Hand);
                screen->setMouseCursor(cursor);
            } else if (sorted && mousePosition.y >= 70.f && mousePosition.y <= 100.f &&
                mousePosition.x >= 1480.f && mousePosition.x <= 1530.f) {
                cursor.loadFromSystem(sf::Cursor::Hand);
                screen->setMouseCursor(cursor);
                sorting.setColor(sf::Color(155, 155, 161));
            } else if (mousePosition.y >= 70.f && mousePosition.y <= 100.f &&
                       mousePosition.x >= newArray.getLocalBounds().width + 260.f &&
                       mousePosition.x <= newArray.getLocalBounds().width + 360.f) {
                cursor.loadFromSystem(sf::Cursor::Text);
                screen->setMouseCursor(cursor);
            } else if (sorted) {
                sorting.setFillColor(sf::Color::White);
                textGenerate.setColor(sf::Color::White);
                moving.setFillColor(sf::Color::White);
                sizeOfArray.setColor(sf::Color::Black);
                cursor.loadFromSystem(sf::Cursor::Arrow);
                screen->setMouseCursor(cursor);
            }
        }

        void render() {
            screen->clear(sf::Color::White);

            if (bubbleSort) {
                bubble_sort();
            }

            using namespace std::literals;
            auto p = 0.00000008ms;
            std::this_thread::sleep_for(p);

            for (auto& rec : vec) {
                screen->draw(*rec);
            }
            screen->draw(background);
            screen->draw(textGenerate);
            screen->draw(sorting);
            screen->draw(newArray);
            screen->draw(moving);
            screen->draw(s1);
            screen->draw(button);
            screen->draw(sizeOfArray);
            screen->draw(s);
            screen->draw(range);
            screen->display();
        }

        void bubble_sort() {
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
                vec[j]->setFillColor(sf::Color::Red);
                vec[j + 1]->setFillColor(sf::Color::Red);
                if (vec[j + 1]->getSize().y < vec[j]->getSize().y) {
                    auto temp = vec[j]->getSize().y;
                    vec[j]->setSize({vec[j]->getSize().x, vec[j + 1]->getSize().y});
                    vec[j + 1]->setSize({vec[j + 1]->getSize().x, temp});
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
        }


        std::unique_ptr<sf::RenderWindow> screen;
        std::vector<std::unique_ptr<sf::RectangleShape>> vec;

        sf::Time TimePerFrame = sf::seconds(1.f / 120.f);
        sf::Sprite background;
        sf::Texture textureBackground;
        sf::Font font;
        sf::Text textGenerate, sorting, newArray;
        sf::RectangleShape s1, moving;
        sf::Cursor cursor;
        sf::CircleShape button;
        sf::Text sizeOfArray, range;
        sf::RectangleShape s;

        std::string size;

        bool sorted = true;
        bool isPressed = false;
        bool was = false;
        bool isClicked = false;
        bool passed = false;
        bool bubbleSort = false;

        int i = 0;
        int j = 0;
        int left = 0;
        int count = 0;
};


int main() {
    Vis v;
    v.run();
}
