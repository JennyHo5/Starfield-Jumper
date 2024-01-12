#pragma once
#include <random>

// Function to generate a random number between 1 and max
inline int GetRandom(int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, max);

	return dis(gen);
}