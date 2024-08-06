#include "Geometry.h"

//Polygon functions --------------------------------

Polygon::Polygon()
{
    n = 1;
    col = WHITE;
    rad = 0.;
    arr = new Vector2d[1];
    arr[0] = Vector2d();
}

Polygon::Polygon(int _n, Vector2d* _arr, uint32_t _col, float _rad)
{
    n = _n;
    col = _col;
    rad = _rad;
    arr = new Vector2d[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = _arr[i];
    }
}

Polygon::Polygon(int _n, Vector2d* _arr, uint32_t _col)
: Polygon(_n, _arr, _col, 0.) {}

Polygon::Polygon(int _n, Vector2d* _arr)
: Polygon(_n, _arr, WHITE) {}

Polygon::Polygon(const Polygon& _other)
{
    n = _other.getN();
    col = _other.getColor();
    rad = _other.getRad();
    arr = new Vector2d[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = _other[i];
    }
}

Polygon::Polygon(Polygon&& _other)
{
    n = _other.getN();
    col = _other.getColor();
    rad = _other.getRad();
    arr = _other.arr;
    _other.arr = nullptr;
}

Polygon& Polygon::operator=(const Polygon& _other)
{
    delete[] arr;
    n = _other.getN();
    col = _other.getColor();
    rad = _other.getRad();
    arr = new Vector2d[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = _other[i];
    };

    return *this;
}

Polygon& Polygon::operator=(Polygon&& _other)
{
    delete[] arr;
    n = _other.getN();
    col = _other.getColor();
    rad = _other.getRad();
    arr = _other.arr;
    _other.arr = nullptr;

    return *this;
}

Polygon::~Polygon()
{
    delete[] arr;
    arr = nullptr;
}

int Polygon::getN() const
{
    return n;
}

uint32_t Polygon::getColor() const
{
    return col;
}

void Polygon::setColor(uint32_t _col)
{
    col = _col;
}

float Polygon::getRad() const
{
    return rad;
}

void Polygon::setRad(float _rad)
{
    rad = _rad;
}



//Polygon operators --------------------------------

Polygon Polygon::operator+(const Vector2d& _other) const
{
    Vector2d* tmp = new Vector2d[n];
    for (int i = 0; i < n; i++)
    {
        tmp[i] = arr[i] + _other;
    }
    return Polygon(n, tmp, col, rad);
}

Polygon Polygon::operator-(const Vector2d& _other) const
{
    return (*this) + -_other;
}

Polygon Polygon::operator*(const float& _other) const
{
    Vector2d* tmp = new Vector2d[n];
    for (int i = 0; i < n; i++)
    {
        tmp[i] = _other * arr[i];
    }
    return Polygon(n, tmp, col, _other * rad);
}

Vector2d Polygon::operator[](const int& _other) const
{
    return arr[_other];
}

Polygon operator+(const Vector2d& _left, const Polygon& _right)
{
    return _right + _left;
}

Polygon operator*(const float& _left, const Polygon& _right)
{
    return _right * _left;
}

Polygon operator*(const Matrix2d& _left, const Polygon& _right)
{
    Vector2d* tmp = new Vector2d[_right.getN()];
    for (int i = 0; i < _right.getN(); i++)
    {
        tmp[i] = _left * _right[i];
    }
    return Polygon(_right.getN(), tmp, _right.getColor(), _right.getRad());
}
