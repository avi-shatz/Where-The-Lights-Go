#include "utilities.h"
#include <chrono>

// getting a true random number between min - max
size_t random_generator(size_t min, size_t max) {
	std::mt19937 rng;
	//rng.seed(std::random_device()());
	rng.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<std::mt19937::result_type>  dist((int)min, (int)max);

	return dist(rng);
}

//additional vector2f operations 
namespace operation2f
{
	//calculates distance between 2 vectors
	inline float distance(sf::Vector2f v1, sf::Vector2f v2)
	{
		return length(v1 - v2);
	}

	//Returns length of a given vector
	inline float length(const sf::Vector2f& source)
	{
		return std::sqrt(dot(source, source));
	}

	//calculates dot product of 2 vectors
	inline float dot(const sf::Vector2f& lv, const sf::Vector2f& rv)
	{
		return lv.x * rv.x + lv.y * rv.y;
	}


	//Returns a given vector with its length normalized to 1
	inline sf::Vector2f normalise(sf::Vector2f source)
	{
		float length = std::sqrt(dot(source, source));
		if (length != 0) source /= length;
		return source;
	}
}