#include "Geometry.h"

//Matrix2d functions --------------------------------

Matrix2d::Matrix2d(float _a11, float _a12,
                   float _a21, float _a22)
{
    arr[0][0] = _a11;
    arr[0][1] = _a12;
    arr[1][0] = _a21;
    arr[1][1] = _a22;
}

Matrix2d::Matrix2d(float _a11, float _a22)
: Matrix2d(_a11, 0.,
           0., _a22) {}

Matrix2d::Matrix2d(float _phi)
: Matrix2d(cos(_phi), -sin(_phi),
           sin(_phi), cos(_phi)) {}

float Matrix2d::get(int _i, int _j) const
{
    return arr[_i][_j];
}

void Matrix2d::set(int _i, int _j, float _aij)
{
    arr[_i][_j] = _aij;
}

float Matrix2d::det() const
{
    return arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0];
}

Matrix2d Matrix2d::T() const
{
    return Matrix2d(arr[0][0], arr[1][0],
                    arr[0][1], arr[1][1]);
}

Matrix2d Matrix2d::inv() const
{
    return Matrix2d(arr[1][1], -arr[0][1],
                    -arr[1][0], arr[0][1]) * (1./(*this).det());
}

void Matrix2d::print()
{
    printf("| %f %f |\n| %f %f |\n",
           arr[0][0], arr[0][1],
           arr[1][0], arr[1][1]);
}



//Matrix2d operators --------------------------------

Matrix2d Matrix2d::operator+() const
{
    return *this;
}

Matrix2d Matrix2d::operator+(const Matrix2d& _other) const
{
    return Matrix2d(arr[0][0] + _other.get(0, 0),
                    arr[0][1] + _other.get(0, 1),
                    arr[1][0] + _other.get(1, 0),
                    arr[1][1] + _other.get(1, 1));
}

Matrix2d Matrix2d::operator*(const float& _other) const
{
    return Matrix2d(arr[0][0] * _other, arr[0][1] * _other,
                    arr[1][0] * _other, arr[1][1] * _other);
}

Matrix2d Matrix2d::operator-() const
{
    return *this * -1;
}

Matrix2d Matrix2d::operator-(const Matrix2d& _other) const
{
    return *this + -_other;
}

Matrix2d Matrix2d::operator*(const Matrix2d& _other) const
{
    return Matrix2d(arr[0][0] * _other.get(0, 0) + arr[0][1] * _other.get(1, 0),
                    arr[0][0] * _other.get(0, 1) + arr[0][1] * _other.get(1, 1),
                    arr[1][0] * _other.get(0, 0) + arr[1][1] * _other.get(1, 0),
                    arr[1][0] * _other.get(0, 1) + arr[1][1] * _other.get(1, 1));
}

Vector2d Matrix2d::operator*(const Vector2d& _other) const
{
    return Vector2d(arr[0][0] * _other.getX() + arr[0][1] * _other.getY(),
                    arr[1][0] * _other.getX() + arr[1][1] * _other.getY());
}

Matrix2d operator*(const float& _left, const Matrix2d& _right)
{
    return _left * _right;
}

Vector2d operator*(const Vector2d& _left, const Matrix2d& _right)
{
    return _right.T() * _left;
}
