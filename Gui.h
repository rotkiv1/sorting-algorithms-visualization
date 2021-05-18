#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

class Gui {
    public:
        Gui();

        void run();

    private:

        void processEvents();

        void handleInput(sf::Keyboard::Key name);

        void handlePlayerInput(sf::Mouse::Button key, bool pressed);

        void update(sf::Time deltaTime);

        void updateFront();

        void render();

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

#endif
