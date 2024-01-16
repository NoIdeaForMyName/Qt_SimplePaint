#pragma once
#include "Path.h"

#define _USE_MATH_DEFINES
#include <cmath>

#define ACCURACY 0.01

class Spiral : public Path
{
public:
	Spiral(const Point& position, double a, double b, double start, double end);
	Spiral(const Spiral& toCopy);
	~Spiral() override = default;

	Item* clone() const override;

private:
	static std::vector<Point> computeSpiral(const Point& pos, double a, double b, double start, double end);
};
