#include "Spiral.h"


Spiral::Spiral(const Point& position, double a, double b, double start, double end)
	: Path(Spiral::computeSpiral(position, a, b, start, end))
{}

Spiral::Spiral(const Spiral& toCopy)
	: Path(toCopy.points)
{}

Item* Spiral::clone() const
{
	return new Spiral(*this);
}

std::vector<Point> Spiral::computeSpiral(const Point& pos, double a, double b, double start, double end)
{
	std::vector<Point> spiral;
	Point minPoint(INT_MAX, INT_MAX);
	while (end - start > 2 * ACCURACY)
	{
		double r = a * pow(M_E, b * start);
		int x = round(r * cos(start));
		int y = -round(r * sin(start));
		Point p(x, y);
		if (p.getX() < minPoint.getX()) minPoint.setX(p.getX());
		if (p.getY() < minPoint.getY()) minPoint.setY(p.getY());
		//p.shift(pos);
		start += ACCURACY;

		spiral.push_back(p);
	}
	minPoint.setX(-minPoint.getX() + pos.getX());
	minPoint.setY(-minPoint.getY() + pos.getY());
	for (Point& p : spiral)
		p.shift(minPoint);

	return spiral; // COPY ELISION
}
