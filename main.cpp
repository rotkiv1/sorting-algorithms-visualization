#include <SFML/Graphics.hpp>

#include <iostream>
#include <chrono>
#include <random>
#include <thread>
#include <memory>


auto generator = std::default_random_engine(std::random_device()());
std::uniform_int_distribution<int> distribution(50, 750);

class Vis {

    public:

        Vis() {
            screen = std::make_unique<sf::RenderWindow>(sf::VideoMode(1600, 1000), "");

            font.loadFromFile("font.ttf");

            s.setPosition(460.f, 73.5);
            s.setFillColor(sf::Color::Black);
            s.setSize({0.f, 0.f});

            sizeOfArray.setFont(font);
            sizeOfArray.setCharacterSize(16.f);
            sizeOfArray.setFillColor(sf::Color::Black);
            sizeOfArray.setPosition(newArray.getLocalBounds().width + 458.f, 71.f);

            textGenerate.setFont(font);
            textGenerate.setCharacterSize(15);
            textGenerate.setPosition(25.f, 70.f);
            textGenerate.setFillColor(sf::Color::White);
            textGenerate.setString("Generate  New  Array");

            newArray.setFont(font);
            newArray.setCharacterSize(15);
            newArray.setPosition(300.f, 70.f);
            newArray.setFillColor(sf::Color::White);
            newArray.setString("Change  array  size  ");

            bubbleSortText.setFont(font);
            bubbleSortText.setCharacterSize(15);
            bubbleSortText.setFillColor(sf::Color::White);
            bubbleSortText.setString("Bubble  sort");
            bubbleSortText.setPosition(700.f, 70.f);

            insertionSortText.setFont(font);
            insertionSortText.setCharacterSize(15);
            insertionSortText.setFillColor(sf::Color::White);
            insertionSortText.setString("Insertion  sort");
            insertionSortText.setPosition(850.f, 70.f);

            heapSortText.setFont(font);
            heapSortText.setCharacterSize(15);
            heapSortText.setFillColor(sf::Color::White);
            heapSortText.setString("Heap  sort");
            heapSortText.setPosition(1025.f, 70.f);

            sorting.setFont(font);
            sorting.setCharacterSize(15);
            sorting.setPosition(1480.f, 70.f);
            sorting.setFillColor(sf::Color::White);
            sorting.setString("Sort");

            s1.setFillColor(sf::Color(102, 157, 178));
            s1.setSize({9.f, 100.f});
            s1.setPosition((textGenerate.getLocalBounds().width + 270.f) / 2, 0.f);

            range.setFont(font);
            range.setCharacterSize(15);
            range.setFillColor(sf::Color::White);
            range.setString("[2, 399]");
            range.setPosition(newArray.getLocalBounds().width + 335.f, 90.f);

            moving.setFillColor(sf::Color::White);
            moving.setSize({80.f, 16.f});
            moving.setPosition(newArray.getLocalBounds().width + 310.f, 73.f);

            textureBackground.loadFromFile("pas.png");
            background.setTexture(textureBackground);
            background.setScale(11, 1);
            background.setPosition(0.f, -275.f);
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
                        std::cout << size.back() << ' ';

                    if (!size.empty()) {
                        size.pop_back();
                        passed = true;
                        std::cout << size << '\n';
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
                    s.setPosition(sizeOfArray.getLocalBounds().width + 460.f, 73.5);
                    std::vector<std::unique_ptr<sf::RectangleShape>> temp;
                    auto determine = (size.empty()) ? 0 : std::stoi(size);
                    for (auto i = 0; i < determine; i++) {
                        temp.push_back(std::make_unique<sf::RectangleShape>());
                    }
                    auto moveDistance = 9.f;
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
                        recSize = 3.f;
                        moveDistance = 4.f;
                    } else if (determine >= 340 && determine < 400) {
                        recSize = 2.f;
                        moveDistance = 3.f;
                    } else if (determine > 0 && determine <= 175) {
                        recSize = 8.f;
                        moveDistance = 9.f;
                    }
                    for (auto& rec : temp) {
                        rec->setSize({recSize, distribution(generator)});
                        rec->setPosition({800.f - determine * moveDistance / 2 + move, 150.f});
                        rec->setScale(0.9, 0.9);
                        rec->setFillColor(sf::Color(102, 157, 178));
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
                mousePosition.x >= newArray.getLocalBounds().width + 310.f &&
                mousePosition.x <= newArray.getLocalBounds().width + 410.f) {
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
                        rec->setSize({recSize, distribution(generator)});
                        rec->setFillColor(sf::Color(102, 157, 178));
                    }
                } else if (sorted && mousePosition.x >= 1480.f && mousePosition.x <= 1580.f) {
                    /* start sorting the array */
                    sorted = false;
                    sorting.setColor(sf::Color(255, 79, 89));
                    textGenerate.setColor(sf::Color(255, 79, 89));
                    sizeOfArray.setColor(sf::Color(255, 79, 89));
                    newArray.setColor(sf::Color(255, 79, 89));
                    if (bubbleSortNow) {
                        bubbleSortText.setColor(sf::Color(255, 79, 89));
                    }
                    if (insertionSortNow) {
                        insertionSortText.setColor(sf::Color(255, 79, 89));
                    }
                    if (heapSortNow) {
                        heapSortText.setColor(sf::Color(255, 79, 89));
                    }
                    cursor.loadFromSystem(sf::Cursor::Arrow);
                    screen->setMouseCursor(cursor);
                } else if (mousePosition.x >= 700.f && mousePosition.x <= 800.f && pressed) {
                    bubbleSortNow = true;
                    insertionSortNow = false;
                    heapSortNow = false;
                   // i = 0;
                   // j = 0;
                    bubbleSortText.setColor(sf::Color(97, 251, 100));
                    insertionSortText.setColor(sf::Color::White);
                    heapSortText.setColor(sf::Color::White);
                    left = 0;
                } else if (mousePosition.x >= 850.f && mousePosition.x <= 955.f && pressed) {
                    insertionSortText.setColor(sf::Color(97, 251, 100));
                    bubbleSortText.setColor(sf::Color::White);
                    heapSortText.setColor(sf::Color::White);
                   // i = 0;
                    //j = i - 1;
                    bubbleSortNow = false;
                    insertionSortNow = true;
                    heapSortNow = false;
                    left = 0;
                } else if (mousePosition.x >= 1025.f && mousePosition.x <= 1100.f && pressed) {
                    insertionSortText.setColor(sf::Color::White);
                    bubbleSortText.setColor(sf::Color::White);
                    heapSortText.setColor(sf::Color(97, 251, 100));
                    //i = vec.size() / 2 - 1;
                    //j = vec.size() - 1;
                    bubbleSortNow = false;
                    insertionSortNow = false;
                    heapSortNow = true;
                    left = 0;
                }
            }
        }

        void update(sf::Time deltaTime) {
            sf::Vector2i position = sf::Mouse::getPosition(*screen);
            sf::Vector2f mousePosition = screen->mapPixelToCoords(position);
            if (sorted && mousePosition.y >= 70.f && mousePosition.y <= 100.f &&
                mousePosition.x >= 25.f && mousePosition.x <= 200.f) {
                textGenerate.setColor(sf::Color(97, 251, 100));
                cursor.loadFromSystem(sf::Cursor::Hand);
                screen->setMouseCursor(cursor);
            } else if (sorted && mousePosition.y >= 70.f && mousePosition.y <= 100.f &&
                mousePosition.x >= 1480.f && mousePosition.x <= 1530.f) {
                cursor.loadFromSystem(sf::Cursor::Hand);
                screen->setMouseCursor(cursor);
                sorting.setColor(sf::Color(97, 251, 100));
            } else if (sorted && mousePosition.y >= 70.f && mousePosition.y <= 100.f &&
                       mousePosition.x >= newArray.getLocalBounds().width + 310.f &&
                       mousePosition.x <= newArray.getLocalBounds().width + 410.f) {
                cursor.loadFromSystem(sf::Cursor::Text);
                screen->setMouseCursor(cursor);
            } else if (sorted && mousePosition.y >= 70.f && mousePosition.y <= 100.f &&
                       mousePosition.x >= 700.f && mousePosition.x <= 800.f) {
                cursor.loadFromSystem(sf::Cursor::Hand);
                screen->setMouseCursor(cursor);
                bubbleSortText.setColor(sf::Color(97, 251, 100));
            } else if (sorted && mousePosition.y >= 70.f && mousePosition.y <= 100.f &&
                       mousePosition.x >= 850.f && mousePosition.x <= 955.f) {
                cursor.loadFromSystem(sf::Cursor::Hand);
                screen->setMouseCursor(cursor);
                insertionSortText.setColor(sf::Color(97, 251, 100));
            } else if (sorted && mousePosition.y >= 70.f && mousePosition.y <= 100.f &&
                       mousePosition.x >= 1025.f && mousePosition.x <= 1100.f) {
                cursor.loadFromSystem(sf::Cursor::Hand);
                screen->setMouseCursor(cursor);
                heapSortText.setColor(sf::Color(97, 251, 100));
            } else if (sorted) {
                sorting.setFillColor(sf::Color::White);
                textGenerate.setColor(sf::Color::White);
                if (!bubbleSortNow) {
                    bubbleSortText.setColor(sf::Color::White);
                }
                if (!insertionSortNow) {
                    insertionSortText.setColor(sf::Color::White);
                }
                if (!heapSortNow) {
                    heapSortText.setColor(sf::Color::White);
                }
                moving.setFillColor(sf::Color::White);
                newArray.setColor(sf::Color::White);
                sizeOfArray.setColor(sf::Color::Black);
                cursor.loadFromSystem(sf::Cursor::Arrow);
                screen->setMouseCursor(cursor);
            }
        }

        void render() {
            screen->clear(sf::Color::White);

            /*
             *  dodac kolory do qs i heapsorta
             *  zmienic selection sort i heapsort
             *  sprawdzic czy dziala
             *  sformatowac kod
             *  dodac funkcje std::is_sorted() -> jesli true, kolor zielony
             */

            if (!sorted) {
                if (heapSortNow) {
                    heapSort();
                } else if (bubbleSortNow) {
                    bubbleSort();
                    bubbleSortNow = false;
                    sorted = true;
                } else if (insertionSortNow) {
                    insertionSort();
                    insertionSortNow = false;
                    sorted = true;
                }
            }

            for (auto i = 0; i < vec.size(); i++) {
                screen->draw(*vec[i]);
            }

            using namespace std::literals;
            auto p = 0.001ms;
            std::this_thread::sleep_for(p);

            screen->draw(background);
            screen->draw(textGenerate);
            screen->draw(sorting);
            screen->draw(newArray);
            screen->draw(moving);
            screen->draw(button);
            screen->draw(sizeOfArray);
            screen->draw(s);
            screen->draw(range);
            screen->draw(bubbleSortText);
            screen->draw(insertionSortText);
            screen->draw(heapSortText);
            screen->display();
        }

        void updateFront() {
            for (auto i = 0; i < vec.size(); i++) {
                screen->draw(*vec[i]);
            }
            using namespace std::literals;
            auto p = 0.000000001ms;
            std::this_thread::sleep_for(p);
            screen->draw(background);
            screen->draw(textGenerate);
            screen->draw(sorting);
            screen->draw(newArray);
            screen->draw(moving);
            screen->draw(button);
            screen->draw(sizeOfArray);
            screen->draw(s);
            screen->draw(range);
            screen->draw(bubbleSortText);
            screen->draw(insertionSortText);
            screen->draw(heapSortText);
            screen->display();
        }

        void bubbleSort() {
            for (int i = 0; i < vec.size() - 1; i++) {
                for (int j = 0; j < vec.size() - i - 1; j++) {
                    screen->clear(sf::Color::White);
                    vec[j + 1]->setFillColor(sf::Color::Red);
                    vec[j]->setFillColor(sf::Color::Red);
                    updateFront();
                    if (vec[j + 1]->getSize().y < vec[j]->getSize().y) {
                        auto temp = vec[j]->getSize().y;
                        vec[j]->setSize({vec[j]->getSize().x, vec[j + 1]->getSize().y});
                        vec[j + 1]->setSize({vec[j + 1]->getSize().x, temp});
                    }
                    vec[j]->setFillColor(sf::Color(102, 157, 178));
                    vec[j + 1]->setFillColor(sf::Color(102, 157, 178));
                    screen->clear(sf::Color::White);
                    updateFront();
                }
                for (auto k = vec.size() - i - 1; k < vec.size(); k++) {
                    if (vec.size() - i - 1 == 1) {
                        vec.front()->setFillColor(sf::Color(204, 153, 255));
                    }
                    vec[k]->setFillColor(sf::Color(204, 153, 255));
                }
            }
        }

        void insertionSort() {
            for (auto i = 1; i < vec.size(); i++) {
               for (auto k = left; k < vec.size(); k++) {
                    vec[k]->setFillColor(sf::Color(102, 157, 178));
                }
                auto key = vec[i]->getSize().y;
                auto j = i - 1;
                while (j >= 0 && vec[j]->getSize().y > key) {
                    vec[j]->setFillColor(sf::Color::Red);
                    vec[j + 1]->setSize({vec[j + 1]->getSize().x, vec[j]->getSize().y});
                    vec[j + 1]->setFillColor(sf::Color(204, 153, 255));
                    j--;
                    screen->clear(sf::Color::White);
                    updateFront();
                }
                vec[j + 1]->setSize({vec[j + 1]->getSize().x, key});
                left++;
                for (auto k = 0; k < left; k++) {
                    vec[k]->setFillColor(sf::Color(204, 153, 255));
                }
                screen->clear(sf::Color::White);
                updateFront();
            }
        }

        void heapify(int n, int i) {
            auto largest = i;
            auto l = 2 * i + 1;
            auto r = 2 * i + 2;

            if (l < n && vec[l]->getSize().y > vec[largest]->getSize().y) {
                largest = l;
            }

            for (auto& rec : vec) {
                rec->setFillColor(sf::Color(102, 157, 178));
            }

            if (r < n && vec[r]->getSize().y > vec[largest]->getSize().y) {
                largest = r;
            }

            vec[i]->setFillColor(sf::Color::Red);
            vec[largest]->setFillColor(sf::Color::Red);
            if (largest != i) {
                auto temp = vec[i]->getSize().y;
                vec[i]->setSize({vec[i]->getSize().x, vec[largest]->getSize().y});
                vec[largest]->setSize({vec[largest]->getSize().x, temp});
                heapify(n, largest);
            }
        }

        void heapSort() {
            if (!sorted) {
                if (i >= 0) {
                    heapify(vec.size(), i);

                    i--;
                } else {
                    if (j >= 0) {
                        auto temp = vec[0]->getSize().y;
                        vec[0]->setSize({vec[0]->getSize().x, vec[j]->getSize().y});
                        vec[j]->setSize({vec[j]->getSize().x, temp});
                        heapify(j, 0);
                        for (auto k = vec.size() - left - 1; k < vec.size(); k++) {
                            vec[k]->setFillColor(sf::Color(204, 153, 255));
                        }
                        j--;
                        left++;
                    } else {
                        sorted = true;
                    }
                }
            }
            if (sorted) {
                heapSortNow = false;
                for (auto& rec : vec) {
                    rec->setFillColor(sf::Color::Green);
                }
                heapSortNow = false;
            }
        }

        int partition(int low, int high) {
            auto i = low - 1;
            for (auto j = low; j <= high - 1; j++) {
                if (vec[j]->getSize().y < vec[high]->getSize().y) {
                    i++;
                    auto temp = vec[i]->getSize().y;
                    vec[i]->setSize({vec[i]->getSize().x, vec[j]->getSize().y});
                    vec[j]->setSize({vec[j]->getSize().x, temp});
                }
                screen->clear(sf::Color::White);
                updateFront();
            }
            auto temp = vec[i + 1]->getSize().y;
            vec[i + 1]->setSize({vec[i + 1]->getSize().x, vec[high]->getSize().y});
            vec[high]->setSize({vec[high]->getSize().x, temp});
            return i + 1;
        }

        void q(int low, int high) {
            if (low >= high) {
                return;
            }
            auto pivot = partition(low, high);
            q(low, pivot - 1);
            q(pivot + 1, high);
        }

        std::unique_ptr<sf::RenderWindow> screen;
        std::vector<std::unique_ptr<sf::RectangleShape>> vec;

        sf::Time TimePerFrame = sf::seconds(1.f / 120.f);
        sf::Sprite background;
        sf::Texture textureBackground;
        sf::Font font;
        sf::Text textGenerate, sorting, newArray, bubbleSortText,
                 insertionSortText, heapSortText;
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
        bool bubbleSortNow = false;
        bool insertionSortNow = false;
        bool heapSortNow = false;
        bool in = true;

        /*
            bubble sort, i = 0, j = 0;
            selection sort, i = 0, j = i - 1;
            heap sort, i = v.size() / 2  - 1, j = v.size() - 1
        */

        int i = 0;
        int j = 0;
        int left = 0;
        int count = 0;
        float recSize = 8.f;
        int a = 1;
        int keyY;
        int p = 0;
        int n = 0;
        int c = 0;
        int pi = 0;
        int ls = 1;
};


int main() {
    Vis v;
    v.run();
}
