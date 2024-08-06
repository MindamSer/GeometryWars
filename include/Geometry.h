#pragma once

#include "Engine.h"
#include "Defines.h"

class Vector2d
{
private:
    float x;
    float y;

public:
    Vector2d(float _x, float _y);
    Vector2d() = default;
    Vector2d(const Vector2d& _other) = default;
    Vector2d(Vector2d&& _other) = default;
    Vector2d& operator=(const Vector2d& _other) = default;
    Vector2d& operator=(Vector2d&& _other) = default;
    ~Vector2d() = default;

    float getX() const;
    void setX(float _x);
    float getY() const;
    void setY(float _y);

    float getAbs() const;
    float getArg() const;
    Vector2d getNorm() const;
    void normalize();
    Vector2d projection(const Vector2d& _other) const;

    void print();

    Vector2d operator+() const;
    Vector2d operator+(const Vector2d& _other) const;
    Vector2d operator*(const float& _other) const;
    Vector2d operator-() const;
    Vector2d operator-(const Vector2d& _other) const;
    float operator*(const Vector2d& _other) const;
    float operator&(const Vector2d& _other) const;
};

Vector2d operator*(const float& _left, const Vector2d& _right);



class Matrix2d
{
private:
    float arr[2][2];

public:
    Matrix2d(float _a11, float _a12,
             float _a21, float _a22);
    Matrix2d(float _a11, float _a22);
    Matrix2d(float _phi);
    Matrix2d() = default;
    Matrix2d(const Matrix2d& _other) = default;
    Matrix2d(Matrix2d&& _other) = default;
    Matrix2d& operator=(const Matrix2d& _other) = default;
    Matrix2d& operator=(Matrix2d&& _other) = default;
    ~Matrix2d() = default;

    float get(int _i, int _j) const;
    void set(int _i, int _j, float _aij);

    float det() const;
    Matrix2d T() const;
    Matrix2d inv() const;

    void print();

    Matrix2d operator+() const;
    Matrix2d operator+(const Matrix2d& _other) const;
    Matrix2d operator*(const float& _other) const;
    Matrix2d operator-() const;
    Matrix2d operator-(const Matrix2d& _other) const;
    Matrix2d operator*(const Matrix2d& _other) const;
    Vector2d operator*(const Vector2d& _other) const;
};

Matrix2d operator*(const float& _left, const Matrix2d& _right);
Vector2d operator*(const Vector2d& _left, const Matrix2d& _right);



class Polygon
{
private:
    int n;
    uint32_t col;
    float rad;
    Vector2d* arr;

public:
    Polygon();
    Polygon(int _n, Vector2d* _arr, uint32_t _col, float _rad);
    Polygon(int _n, Vector2d* _arr, uint32_t _col);
    Polygon(int _n, Vector2d* _arr);
    Polygon(const Polygon& _other);
    Polygon(Polygon&& _other);
    Polygon& operator=(const Polygon& _other);
    Polygon& operator=(Polygon&& _other);
    ~Polygon();

    int getN() const;
    uint32_t getColor() const;
    void setColor(uint32_t _col);
    float getRad() const;
    void setRad(float _rad);

    Polygon operator+(const Vector2d& _other) const;
    Polygon operator-(const Vector2d& _other) const;
    Polygon operator*(const float& _other) const;
    Vector2d operator[](const int& _other) const;
};

Polygon operator+(const Vector2d& _left, const Polygon& _right);
Polygon operator*(const float& _left, const Polygon& _right);
Polygon operator*(const Matrix2d& _left, const Polygon& _right);
