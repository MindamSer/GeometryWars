#include "GameClasses.h"

//Entity functions --------------------------------

Entity::Entity(Vector2d _pos, Vector2d _vel, Vector2d _acc,
               float _phi, float _omega, Polygon _sprite)
: pos(_pos), vel(_vel), acc(_acc),
phi(_phi), omega(_omega), sprite(_sprite) {}

Vector2d Entity::getPos() const
{
    return pos;
}

void Entity::setPos(Vector2d _pos)
{
    pos = _pos;
}

Vector2d Entity::getVel() const
{
    return vel;
}

void Entity::setVel(Vector2d _vel)
{
    vel = _vel;
}

Vector2d Entity::getAcc() const
{
    return acc;
}

void Entity::setAcc(Vector2d _acc)
{
    acc = _acc;
}

float Entity::getPhi() const
{
    return phi;
}

void Entity::setPhi(float _phi)
{
    phi = _phi;
}

float Entity::getOmega() const
{
    return omega;
}

void Entity::setOmega(float _omega)
{
    omega = _omega;
}

Polygon Entity::getSprite() const
{
    return sprite;
}

void Entity::setSprite(Polygon _sprite)
{
    sprite = _sprite;
}

uint32_t Entity::getColor() const
{
    return sprite.getColor();
}

void Entity::setColor(uint32_t _color)
{
    sprite.setColor(_color);
}

float Entity::getRad() const
{
    return sprite.getRad();
}

void Entity::setRad(float _rad)
{
    sprite.setRad(_rad);
}

void Entity::draw() const
{
    draw_poly(Matrix2d(phi) * sprite + pos);
}

void Entity::update(float _dt, float _time)
{
    vel = vel + acc * _dt;
    pos = pos + vel * _dt;
    float t = (phi + omega * _dt + 2 * M_PI) / (2 * M_PI);
    phi = 2 * M_PI * (t - floor(t));
}

bool collision(const Entity &left, const Entity &right)
{
    return (left.getSprite().getRad() + right.getSprite().getRad()) >
    (left.getPos() - right.getPos()).getAbs();
}
