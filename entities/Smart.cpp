#include "GameClasses.h"

//SmartEnt functions --------------------------------

SmartEnt::SmartEnt(Vector2d _pos, Vector2d _vel,
                   float _omega, Polygon _sprite,
                   int _lvl, float _max_speed,
                   float _max_invul_time, int _blink_freq)
: Entity(_pos, _vel, Vector2d(),
         0., _omega, _sprite)
{
    max_speed = _max_speed;

    max_invul_time = _max_invul_time;
    invul_time = _max_invul_time;
    blink_freq = _blink_freq;

    level = _lvl;
}

float SmartEnt::getMaxSp() const
{
    return max_speed;
}

void SmartEnt::setMaxSp(float _ms)
{
    max_speed = _ms;
}

float SmartEnt::getMIT() const
{
    return max_invul_time;
}

void SmartEnt::setMIT(float _it)
{
    max_invul_time = _it;
}

float SmartEnt::getIT() const
{
    return invul_time;
}

void SmartEnt::setIT(float _it)
{
    invul_time = _it;
}

int SmartEnt::getLV() const
{
    return level;
}

void SmartEnt::setLV(int _lvl)
{
    level = _lvl;
}

void SmartEnt::draw() const
{
    draw_poly(Matrix2d(phi) * sprite + pos,
              0.5 + 0.5 * ((invul_time <= 0.) ||
              ((int(2 * blink_freq * invul_time) + 1) % 2)));
}

void SmartEnt::update(float _dt, float _time)
{
    vel = vel + acc * _dt;
    if (vel.getAbs() > max_speed)
    {
        vel = vel.getNorm() * max_speed;
    }

    pos = pos + vel * _dt;
    if ((pos.getX() < 0) || (pos.getX() > SCREEN_WIDTH))
    {
        vel = Matrix2d(-1, 1) * vel;
        pos = pos + vel * _dt;
    }
    if ((pos.getY() < 0) || (pos.getY() > SCREEN_HEIGHT))
    {
        vel = Matrix2d(1, -1) * vel;
        pos = pos + vel * _dt;
    }

    float t = (phi + omega * _dt + 2 * M_PI) / (2 * M_PI);
    phi = 2 * M_PI * (t - floor(t));

    if (invul_time > 0)
    {
        invul_time -= _dt;
    }
}
