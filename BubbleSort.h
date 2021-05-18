#ifndef BUBBLESORT_H_INCLUDED
#define BUBBLESORT_H_INCLUDED

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <functional>

class BubbleSort {
    public:
        BubbleSort() = default;

        void bubbleSort(std::shared_ptr<sf::RenderWindow> screen,
                        std::vector<sf::RectangleShape>& vec,
                        std::function<void()> updateScreen);
};

#endif
