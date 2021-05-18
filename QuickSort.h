#ifndef QUICKSORT_H_INCLUDED
#define QUICKSORT_H_INCLUDED

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <functional>

class QuickSort {
    public:
        QuickSort() = default;

        int partition(std::shared_ptr<sf::RenderWindow> screen,
                      std::vector<sf::RectangleShape>& vec,
                      std::function<void()> updateScreen,
                      int low, int high);

        void quickSort(std::shared_ptr<sf::RenderWindow> screen,
                       std::vector<sf::RectangleShape>& vec,
                       std::function<void()> updateScreen,
                       int low, int high);
};

#endif
