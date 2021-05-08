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
            screen = std::make_unique<sf::RenderWindow>(sf::VideoMode(1200, 1000), "");
            for (auto i = 0; i < 200; i++) {
                vec.push_back(std::make_unique<sf::RectangleShape>());
            }
            auto move = 0.f;
            for (auto& rec : vec) {
                rec->setSize({5.f, -distribution(generator)});
                rec->setPosition({0.f + move, 1000.f});
                move += 6.f;
            }

            for (auto i = 0; i < 10; i++) {
                    std::cout << distribution(generator) << '\n';
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

        void handlePlayerInput(sf::Mouse::Button key, bool isPressed) {
            for (auto& rec : vec) {
                rec->setSize({9.f, -distribution(generator)});
                rec->setFillColor(sf::Color::White);
            }
            left = 0;
            i = 0;
            j = 0;
        }

        void update(sf::Time deltaTime) {




        }

        void render() {
            screen->clear();
            if (i >= vec.size() - 1 && j >= vec.size() - 1) {
                sorted = true;
                //std::cout << i << ' ' << j;
            }

            for (auto k = 0; k < vec.size() - left; k++) {
                vec[k]->setFillColor(sf::Color::White);
            }

            if (!sorted) {
                vec[j]->setFillColor(sf::Color::Green);                vec[j + 1]->setFillColor(sf::Color::Green);
                if (vec[j + 1]->getSize().y > vec[j]->getSize().y) {
                    auto temp = vec[j]->getSize().y;
                    vec[j]->setSize({5.f, vec[j + 1]->getSize().y});
                    vec[j + 1]->setSize({5.f, temp});
                    vec[j]->setFillColor(sf::Color::Red);                    vec[j + 1]->setFillColor(sf::Color::Red);
                }
                j++;
                if (j == vec.size() - left - 1) {
                    for (auto k = vec.size() - left - 1; k < vec.size(); k++) {
                        vec[k]->setFillColor(sf::Color::Magenta);
                        std::cout << vec.size() - left - 1 << '\n';
                    }
                    j = 0;
                    i++;
                    left++;
                }
            }
            using namespace std::literals;
            std::this_thread::sleep_for(0.00000001ms);
            for (auto& rec : vec) {
                screen->draw(*rec);
            }
            screen->display();
        }


        std::unique_ptr<sf::RenderWindow> screen;
        sf::Time TimePerFrame = sf::seconds(1.f / 15.f);
        std::vector<std::unique_ptr<sf::RectangleShape>> vec;
        bool sorted = false;
        int i = 0;
        int j = 0;
        int left = 0;
};


int main() {
    Vis v;
    v.run();
}
