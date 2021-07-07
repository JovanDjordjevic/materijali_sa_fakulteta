//prekopirao samo njegov kod

#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <string>

namespace matf{
    class Point
    {
    public:
        Point(double x = 0.0, double y = 0.0)
            : x(x), y(y)
        {
            std::cout << "ctor: x=" << x << ", y=" << y << std::endl;
        }

        Point(const Point &p)
            : x(p.x), y(p.y)
        {
            std::cout << "copy ctor: arg=" << p.str() << std::endl;
        }

        Point(Point &&p) noexcept
            : x(p.x), y(p.y)
        {
            std::cout << "move ctor " << p.str() << std::endl;
        }

        Point operator++(int)
        {
            Point tmp(*this);
            x += 1;
            y += 1;
            return tmp;
        }

        Point &operator=(const Point &p)
        {
            auto tmp(p);
            std::swap(tmp.x, x);
            std::swap(tmp.y, y);
            std::cout << "operator =: " << p.str() << std::endl;
            return *this;
        }

        Point &operator=(Point &&p) noexcept
        {
            std::cout << "operator = &&: " << p.str() << std::endl;
            std::swap(p.x, x);
            std::swap(p.y, y);
            return *this;
        }

        Point operator+(const Point &p) const
        {
            std::cout << "operator +: " << this->str() << ", " << p.str() << std::endl;
            return Point(x + p.x, p.y + y);
        }

        std::string str() const
        {
            return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
        }

        double x, y;
    };
}

#endif /* ifndef POINT_HPP */
