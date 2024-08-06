#include "GameClasses.h"

//StupidEnt functions --------------------------------

StupidEnt::StupidEnt(Vector2d _pos, Vector2d _vel,
                     float _phi, Polygon _sprite,
                     float _ttl)
: Entity(_pos, _vel, Vector2d(),
         _phi, 0., _sprite)
{
    ttl = _ttl;
}

float StupidEnt::getTTL() const
{
    return ttl;
}

void StupidEnt::setTTL(float _ttl)
{
    ttl = _ttl;
}

void StupidEnt::update(float _dt, float _time)
{
    pos = pos + vel * _dt;
    ttl -= _dt;
}



//BulletEnt functions --------------------------------

BulletEnt::BulletEnt(Vector2d _pos, Vector2d _vel,
                     float _phi, Polygon _sprite)
: StupidEnt(_pos, _vel,
            _phi, _sprite,
            BULLET_TTL) {}



//ParticleEnt functions --------------------------------

ParticleEnt::ParticleEnt(Vector2d _pos, Vector2d _vel,
                         float _phi, Polygon _sprite)
: StupidEnt(_pos, _vel,
            _phi, _sprite,
            PARTICLES_TTL) {}

void ParticleEnt::draw() const
{
    draw_poly(Matrix2d(phi) * sprite + pos, ttl / PARTICLES_TTL);
}
