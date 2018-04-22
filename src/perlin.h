#ifndef PERLIN_H
#define PERLIN_H

#include <vector>
#include <iostream>
/* This code is mostly written by Solarian */

class PerlinNoise {
	std::vector<int> p;
public:
	PerlinNoise();
	PerlinNoise(unsigned int seed);
	double noise(double x, double y, double z);

private:

    double fade(double t);
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y, double z);
};

#endif