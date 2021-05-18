#ifndef HEAPSORT_H_INCLUDED
#define HEAPSORT_H_INCLUDED

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <functional>

class HeapSort {
    public:
        HeapSort() = default;

        void heapify(std::shared_ptr<sf::RenderWindow> screen,
                     std::vector<sf::RectangleShape>& vec,
                     std::function<void()> updateScreenint,
                     int n, int i, int left);

        void heapSort(std::shared_ptr<sf::RenderWindow> screen,
                      std::vector<sf::RectangleShape>& vec,
                      std::function<void()> updateScreen,
                      int& left);

};

#endif
