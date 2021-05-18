#ifndef INSERTIONSORT_H_INCLUDED
#define INSERTIONSORT_H_INCLUDED

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <functional>

class InsertionSort {
    public:
        InsertionSort() = default;

        void insertionSort(std::shared_ptr<sf::RenderWindow> screen,
                           std::vector<sf::RectangleShape>& vec,
                           std::function<void()> updateScreen,
                           int& left);
};

#endif
