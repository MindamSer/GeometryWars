#include "Geometry.h"

//Vector2d functions --------------------------------

Vector2d::Vector2d(float _x, float _y)
: x(_x), y(_y) {}

float Vector2d::getX() const
{
    return x;
}

void Vector2d::setX(float _x)
{
    x = _x;
}

float Vector2d::getY() const
{
    return y;
}

void Vector2d::setY(float _y)
{
    y = _y;
}

float Vector2d::getAbs() const
{
    return sqrt(x*x + y*y);
}

float Vector2d::getArg() const
{
    float a = -atan(y / x) + 2 * M_PI;
    if (x < 0)
    {
        a += M_PI;
    }
    a = a / (2 * M_PI);
    return 2 * M_PI * (a - floor(a));
}

Vector2d Vector2d::getNorm() const
{
    float l = getAbs();
    return Vector2d(x / l, y / l);
}

void Vector2d::normalize()
{
    float l = getAbs();
    x = x / l;
    y = y / l;
}

Vector2d Vector2d::projection(const Vector2d& _other) const
{
    float dot = (*this) * _other;
    float proj = dot / _other.getAbs();

    return Vector2d(_other) * (proj / _other.getAbs());
}

void Vector2d::print()
{
    printf("{%f; %f}\n", x, y);
}



//Vector2d operators --------------------------------

Vector2d Vector2d::operator+() const
{
    return *this;
}

Vector2d Vector2d::operator+(const Vector2d& _other) const
{
    return Vector2d(x + _other.getX(), y + _other.getY());
}

Vector2d Vector2d::operator*(const float& _other) const
{
    return Vector2d(x * _other, y * _other);
}

Vector2d Vector2d::operator-() const
{
    return *this * -1;
}

Vector2d Vector2d::operator-(const Vector2d& _other) const
{
    return *this + -_other;
}

float Vector2d::operator*(const Vector2d& _other) const
{
    return x * _other.getX() + y * _other.getY();
}

float Vector2d::operator&(const Vector2d& _other) const
{
    return x * _other.getY() - _other.getX() * y;
}

Vector2d operator*(const float& _left, const Vector2d& _right)
{
    return _right * _left;
}
