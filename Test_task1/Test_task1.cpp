// Test_task1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <chrono>

#include "ThreadPool.h"


void sum() {
    std::random_device rnd_device;
    // Specify the engine and distribution.
    std::mt19937 mersenne_engine{ rnd_device() };  // Generates random integers
    std::uniform_int_distribution<int> dist{ 1, 52 };

    auto gen = [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    };

    std::vector<int> arr(1000);
    std::generate(begin(arr), end(arr), gen);
    int ans = 0;
    for (int i = 0; i < arr.size(); ++i) {
        ans += arr[i];
    }
}

int main()
{
    auto curTime = std::chrono::steady_clock::now();
    auto prevTime = curTime;

    ThreadPool threadPool(3);
    
    auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(curTime - prevTime).count() / 1000000.0f;
    prevTime = curTime;
    std::cout << deltaTime << "\n";

    auto id1 = threadPool.addTask(&sum);
    auto id2 = threadPool.addTask(&sum);
    auto id3 = threadPool.addTask(&sum);
    auto id4 = threadPool.addTask(&sum);
    auto id5 = threadPool.addTask(&sum);
    
    deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(curTime - prevTime).count() / 1000000.0f;
    prevTime = curTime;
    std::cout << deltaTime << "\n";

    threadPool.wait(id1);
    
    deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(curTime - prevTime).count() / 1000000.0f;
    prevTime = curTime;
    std::cout << deltaTime << "\n";

    threadPool.waitAll();

    deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(curTime - prevTime).count() / 1000000.0f;
    prevTime = curTime;
    std::cout << deltaTime << "\n";
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
