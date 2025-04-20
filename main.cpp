#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <string>
#include "Button.hpp"
#include "Slider.hpp"

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 700;
const int NUM_BARS = 120;
int delay = 10;

// 🎵 Play sound
void playTone(float pitch = 1.0f) {
    static sf::SoundBuffer buffer;
    static sf::Sound sound;
    static bool initialized = false;

    if (!initialized) {
        if (!buffer.loadFromFile("beep.wav")) {
            std::cerr << "Failed to load beep.wav\n";
        }
        sound.setBuffer(buffer);
        initialized = true;
    }

    sound.setPitch(pitch);
    sound.play();
}

// 🔢 Generate random bars
std::vector<int> generateRandomArray(int size, int maxHeight) {
    std::vector<int> arr(size);
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(10, maxHeight - 150);
    for (int &val : arr) val = dist(rng);
    return arr;
}

// 📊 Draw bars
void drawBars(sf::RenderWindow &window, const std::vector<int> &arr, int highlight1 = -1, int highlight2 = -1) {
    float barWidth = static_cast<float>(WINDOW_WIDTH) / arr.size();
    for (size_t i = 0; i < arr.size(); ++i) {
        sf::RectangleShape bar(sf::Vector2f(barWidth - 1, arr[i]));
        bar.setPosition(i * barWidth, WINDOW_HEIGHT - arr[i] - 60);
        bar.setFillColor(i == highlight1 || i == highlight2 ? sf::Color::Red : sf::Color(100, 200, 250));
        window.draw(bar);
    }
}

// ⏱ Time text
void drawTime(sf::RenderWindow &window, sf::Font &font, float ms) {
    sf::Text timeText("Sort Time: " + std::to_string(static_cast<int>(ms)) + " ms", font, 20);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(10, WINDOW_HEIGHT - 40);
    window.draw(timeText);
}

// Sorting Algorithms (same as before, just make sure each draw happens inside main render loop)
void bubbleSort(sf::RenderWindow &window, std::vector<int> &arr, int delay) {
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                playTone(1.2f);
            } else playTone(0.8f);

            window.clear(sf::Color(30, 30, 30));
            drawBars(window, arr, j, j + 1);
            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
    }
}

void insertionSort(sf::RenderWindow &window, std::vector<int> &arr, int delay) {
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;

            window.clear(sf::Color(30, 30, 30));
            drawBars(window, arr, j, j + 1);
            window.display();
            playTone();
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
        arr[j + 1] = key;
    }
}

// Add mergeSort, quickSort, etc. here similarly

// Main function
int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sorting Visualizer", sf::Style::Close);
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Font failed to load\n";
        return -1;
    }

    std::vector<int> arr = generateRandomArray(NUM_BARS, WINDOW_HEIGHT);

    // Buttons
    Button bubbleBtn(10, 10, 130, 40, "Bubble Sort");
    Button insertBtn(150, 10, 130, 40, "Insertion");
    Button shuffleBtn(290, 10, 130, 40, "Shuffle");
    Button exitBtn(430, 10, 130, 40, "Exit");

    // Search (temporarily placed)
    Button linearBtn(580, 10, 150, 40, "Linear Search");

    // Slider
    Slider speedSlider(10, 60, 300, 1, 100, delay);

    float sortTime = 0.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            sf::Vector2f mouse(sf::Mouse::getPosition(window));

            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                delay = static_cast<int>(speedSlider.getValue());
                auto start = std::chrono::high_resolution_clock::now();

                if (bubbleBtn.isClicked(mouse)) bubbleSort(window, arr, delay);
                else if (insertBtn.isClicked(mouse)) insertionSort(window, arr, delay);
                else if (shuffleBtn.isClicked(mouse)) arr = generateRandomArray(NUM_BARS, WINDOW_HEIGHT);
                else if (exitBtn.isClicked(mouse)) window.close();
                else if (linearBtn.isClicked(mouse)) {
                    int target = arr[arr.size() / 3];
                    for (size_t i = 0; i < arr.size(); ++i) {
                        window.clear(sf::Color(30, 30, 30));
                        drawBars(window, arr, i);
                        playTone(arr[i] == target ? 1.5f : 0.7f);
                        window.display();
                        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                        if (arr[i] == target) break;
                    }
                }

                auto end = std::chrono::high_resolution_clock::now();
                sortTime = std::chrono::duration<float, std::milli>(end - start).count();
            }
        }

        // UI Refresh
        window.clear(sf::Color(30, 30, 30));
        drawBars(window, arr);
        drawTime(window, font, sortTime);

        // Buttons
        bubbleBtn.draw(window);
        insertBtn.draw(window);
        shuffleBtn.draw(window);
        exitBtn.draw(window);
        linearBtn.draw(window);

        speedSlider.draw(window);

        window.display();
    }

    return 0;
}
