//#include <SFML/Graphics.hpp>

#include "BubbleSort.h"
#include "HeapSort.h"
#include "InsertionSort.h"
#include "QuickSort.h"
#include "Gui.h"

/*
auto generator = std::default_random_engine(std::random_device()());
std::uniform_int_distribution<int> distribution(50, 750);

class Gui {

    public:

        Gui()
        : screen(std::make_shared<sf::RenderWindow>(sf::VideoMode(1600, 1000), "")) {

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

            quickSortText.setFont(font);
            quickSortText.setCharacterSize(15);
            quickSortText.setFillColor(sf::Color::White);
            quickSortText.setString("Quick  sort");
            quickSortText.setPosition(1165.f, 70.f);

            sorting.setFont(font);
            sorting.setCharacterSize(15);
            sorting.setPosition(1480.f, 70.f);
            sorting.setFillColor(sf::Color::White);
            sorting.setString("Sort");

            s1.setFillColor(sf::Color(102, 157, 178));
            s1.setSize({9.f, 100.f});
            s1.setPosition((textGenerate.getLocalBounds().width + 270.f) / 2, 0.f);

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
                    if (!size.empty()) {
                        size.pop_back();
                        passed = true;
                    }
                } else {
                    auto curr = static_cast<char>(name);
                    if (curr >= '0' && curr <= '9') {
                        size += curr;
                        passed = true;
                        if (size.size() >= 2 && std::stoi(size) >= 730) {
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
                    std::vector<sf::RectangleShape> temp;
                    auto determine = (size.empty()) ? 0 : std::stoi(size);
                    for (auto i = 0; i < determine; i++) {
                        temp.push_back(sf::RectangleShape());
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
                    } else if (determine >= 340 && determine <= 400) {
                        recSize = 2.f;
                        moveDistance = 3.f;
                    } else if (determine > 0 && determine <= 175) {
                        recSize = 8.f;
                        moveDistance = 9.f;
                    } else {
                        recSize = 1.f;
                        moveDistance = 2.f;
                    }
                    for (auto& rec : temp) {
                        rec.setSize({recSize, distribution(generator)});
                        rec.setPosition({800.f - determine * moveDistance / 2 + move, 150.f});
                        rec.setScale(0.9, 0.9);
                        rec.setFillColor(sf::Color(102, 157, 178));
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
                        rec.setSize({recSize, distribution(generator)});
                        rec.setFillColor(sf::Color(102, 157, 178));
                    }
                } else if (sorted && mousePosition.x >= 1480.f && mousePosition.x <= 1580.f) {
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
                    if (quickSortNow) {
                        quickSortText.setColor(sf::Color(255, 79, 89));
                    }
                    cursor.loadFromSystem(sf::Cursor::Arrow);
                    screen->setMouseCursor(cursor);
                } else if (mousePosition.x >= 700.f && mousePosition.x <= 800.f && pressed) {
                    bubbleSortNow = true;
                    insertionSortNow = false;
                    heapSortNow = false;
                    quickSortNow = false;
                    bubbleSortText.setColor(sf::Color(97, 251, 100));
                    insertionSortText.setColor(sf::Color::White);
                    heapSortText.setColor(sf::Color::White);
                    quickSortText.setColor(sf::Color::White);
                    left = 0;
                } else if (mousePosition.x >= 850.f && mousePosition.x <= 955.f && pressed) {
                    insertionSortText.setColor(sf::Color(97, 251, 100));
                    bubbleSortText.setColor(sf::Color::White);
                    heapSortText.setColor(sf::Color::White);
                    quickSortText.setColor(sf::Color::White);
                    bubbleSortNow = false;
                    insertionSortNow = true;
                    heapSortNow = false;
                    quickSortNow = false;
                    left = 0;
                } else if (mousePosition.x >= 1025.f && mousePosition.x <= 1100.f && pressed) {
                    insertionSortText.setColor(sf::Color::White);
                    bubbleSortText.setColor(sf::Color::White);
                    quickSortText.setColor(sf::Color::White);
                    heapSortText.setColor(sf::Color(97, 251, 100));
                    bubbleSortNow = false;
                    insertionSortNow = false;
                    heapSortNow = true;
                    quickSortNow = false;
                    left = 0;
                } else if (mousePosition.x >= 1165.f && mousePosition.x <= 1230.f && pressed) {
                    insertionSortText.setColor(sf::Color::White);
                    bubbleSortText.setColor(sf::Color::White);
                    quickSortText.setColor(sf::Color(97, 251, 100));
                    heapSortText.setColor(sf::Color::White);
                    bubbleSortNow = false;
                    insertionSortNow = false;
                    heapSortNow = false;
                    quickSortNow = true;
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
            } else if (sorted && mousePosition.x >= 1165.f && mousePosition.x <= 1250.f &&
                       mousePosition.y >= 70.f && mousePosition.y <= 100.f) {
                cursor.loadFromSystem(sf::Cursor::Hand);
                screen->setMouseCursor(cursor);
                quickSortText.setColor(sf::Color(97, 251, 100));
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
                if (!quickSortNow) {
                    quickSortText.setColor(sf::Color::White);
                }
                moving.setFillColor(sf::Color::White);
                newArray.setColor(sf::Color::White);
                sizeOfArray.setColor(sf::Color::Black);
                cursor.loadFromSystem(sf::Cursor::Arrow);
                screen->setMouseCursor(cursor);
            }
        }

        void updateFront() {
            for (auto i = 0; i < vec.size(); i++) {
                screen->draw(vec[i]);
            }
            using namespace std::literals;
            auto p = 0.0000001ms;
            std::this_thread::sleep_for(p);
            screen->draw(background);
            screen->draw(textGenerate);
            screen->draw(sorting);
            screen->draw(newArray);
            screen->draw(moving);
            screen->draw(sizeOfArray);
            screen->draw(s);
            screen->draw(bubbleSortText);
            screen->draw(insertionSortText);
            screen->draw(heapSortText);
            screen->draw(quickSortText);
            screen->display();
        }

        void render() {
            screen->clear(sf::Color::White);
            if (!sorted) {
                if (heapSortNow) {
                    HeapSort h;
                    h.heapSort(screen, vec,
                               [this](){ updateFront(); },
                               left);
                    heapSortNow = false;
                    sorted = true;
                } else if (bubbleSortNow) {
                    BubbleSort b;
                    b.bubbleSort(screen, vec,
                                 [this](){ updateFront(); });
                    bubbleSortNow = false;
                    sorted = true;
                } else if (insertionSortNow) {
                    InsertionSort i;
                    i.insertionSort(screen, vec,
                                    [this](){ updateFront(); },
                                    left);
                    insertionSortNow = false;
                    sorted = true;
                } else if (quickSortNow) {
                    QuickSort q;
                    q.quickSort(screen, vec,
                                [this](){ updateFront(); },
                                0, vec.size() - 1);
                    quickSortNow = false;
                    sorted = true;
                }
            }
            updateFront();
        }

        std::shared_ptr<sf::RenderWindow> screen;
        std::vector<sf::RectangleShape> vec;

        sf::Time TimePerFrame = sf::seconds(1.f / 120.f);
        sf::Sprite background;
        sf::Texture textureBackground;
        sf::Font font;
        sf::Text textGenerate, sorting, newArray, bubbleSortText,
                 insertionSortText, heapSortText, quickSortText,
                 sizeOfArray;
        sf::RectangleShape s1, moving;
        sf::Cursor cursor;
        sf::RectangleShape s;

        std::string size;

        bool sorted = true;
        bool isPressed = false;
        bool isClicked = false;
        bool passed = false;
        bool bubbleSortNow = false;
        bool insertionSortNow = false;
        bool heapSortNow = false;
        bool quickSortNow = false;

        int left = 0;
        float recSize = 8.f;

};

*/
int main() {
    Gui g;
    g.run();
}
