#pragma once

class Point
{
public:
	Point();
	Point(int x, int y);
	Point(const Point& r_toCopy);
	~Point() = default;

	void shift(const Point& p);
	int getX() const;
	int getY() const;
	void setX(int newX);
	void setY(int newY);

private:
	int x;
	int y;
};
