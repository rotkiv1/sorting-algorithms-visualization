#include "HeapSort.h"

void HeapSort::heapify(std::shared_ptr<sf::RenderWindow> screen,
                       std::vector<sf::RectangleShape>& vec,
                       std::function<void()> updateScreen,
                       int n, int i, int left) {
    auto largest = i;
    auto l = 2 * i + 1;
    auto r = 2 * i + 2;
    if (l < n && vec[l].getSize().y > vec[largest].getSize().y) {
        largest = l;
    }
    for (int i = 0; i < vec.size() - left; i++) {
        vec[i].setFillColor(sf::Color(102, 157, 178));
    }
    screen->clear(sf::Color::White);
    updateScreen();
    if (r < n && vec[r].getSize().y > vec[largest].getSize().y) {
        largest = r;
    }
    vec[i].setFillColor(sf::Color::Red);
    vec[largest].setFillColor(sf::Color::Red);
    screen->clear(sf::Color::White);
    updateScreen();
    if (largest != i) {
        auto temp = vec[i].getSize().y;
        vec[i].setSize({vec[i].getSize().x, vec[largest].getSize().y});
        vec[largest].setSize({vec[largest].getSize().x, temp});
        heapify(screen, vec, updateScreen, n, largest, left);
    }
}

void HeapSort::heapSort(std::shared_ptr<sf::RenderWindow> screen,
                        std::vector<sf::RectangleShape>& vec,
                        std::function<void()> updateScreen,
                        int& left) {
    for (int i = vec.size() / 2 - 1; i >= 0; i--) {
        heapify(screen, vec, updateScreen, vec.size(), i, left);
    }
    for (int i = vec.size() - 1; i >= 0; i--) {
        auto temp = vec[0].getSize().y;
        vec[0].setSize({vec[0].getSize().x, vec[i].getSize().y});
        vec[i].setSize({vec[i].getSize().x, temp});
        heapify(screen, vec, updateScreen, i, 0, left);
        for (auto k = vec.size() - left - 1; k < vec.size(); k++) {
            vec[k].setFillColor(sf::Color(204, 153, 255));
        }
        left++;
        screen->clear(sf::Color::White);
        updateScreen();
    }
}
