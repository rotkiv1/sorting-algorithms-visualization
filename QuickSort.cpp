#include "QuickSort.h"

int QuickSort::partition(std::shared_ptr<sf::RenderWindow> screen,
                         std::vector<sf::RectangleShape>& vec,
                         std::function<void()> updateScreen,
                         int low, int high) {
    auto i = low - 1;
    for (auto j = low; j <= high - 1; j++) {
        vec[j].setFillColor(sf::Color::Red);
        vec[high].setFillColor(sf::Color::Red);
        screen->clear(sf::Color::White);
        updateScreen();
        if (vec[j].getSize().y < vec[high].getSize().y) {
            i++;
            auto temp = vec[i].getSize().y;
            vec[i].setSize({vec[i].getSize().x, vec[j].getSize().y});
            vec[j].setSize({vec[j].getSize().x, temp});
        }
        vec[j].setFillColor(sf::Color(102, 157, 178));
        vec[high].setFillColor(sf::Color(102, 157, 178));
        screen->clear(sf::Color::White);
        updateScreen();
    }
    auto temp = vec[i + 1].getSize().y;
    vec[i + 1].setSize({vec[i + 1].getSize().x, vec[high].getSize().y});
    vec[high].setSize({vec[high].getSize().x, temp});
    return i + 1;
}

void QuickSort::quickSort(std::shared_ptr<sf::RenderWindow> screen,
                          std::vector<sf::RectangleShape>& vec,
                          std::function<void()> updateScreen,
                          int low, int high) {
    if (low >= high) {
                return;
            }
            auto pivot = partition(screen, vec, updateScreen, low, high);
            quickSort(screen, vec, updateScreen, low, pivot - 1);
            quickSort(screen, vec, updateScreen, pivot + 1, high);
            for (auto i = low; i <= high; i++) {
                vec[i].setFillColor(sf::Color(204, 153, 255));
            }
            screen->clear(sf::Color::White);
            updateScreen();
}
