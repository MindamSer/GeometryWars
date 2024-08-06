#include "GameClasses.h"

//EnemyEnt functions --------------------------------

EnemyEnt::EnemyEnt(int _x, int _y, Vector2d _vel, Polygon _sprite, int _lvl)
: SmartEnt(Vector2d(_x, _y), _vel,
           ENEMY_OMEGA, _sprite,
           _lvl, ENEMY_MAX_SPEED,
           ENEMY_INVIL, ENEMY_BLINK_FREQ)
{
    max_hit_points = int(ENEMY_HIT_POINTS * (1. + 0.5 * _lvl));
    hit_points = max_hit_points;
}

int EnemyEnt::getMHP() const
{
    return max_hit_points;
}

void EnemyEnt::setMHP(int _mhp)
{
    max_hit_points = _mhp;
}

int EnemyEnt::getHP() const
{
    return hit_points;
}

void EnemyEnt::setHP(int _hp)
{
    hit_points = _hp;
}

void EnemyEnt::update(float _dt, float _time)
{
    if (level > 2)
    {
        vel = vel + acc * _dt;
    }
    if (level > 1)
    {
        float t = (phi + omega * _dt + 2 * M_PI) / (2 * M_PI);
        phi = 2 * M_PI * (t - floor(t));
    }

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

    if (invul_time > 0)
    {
        invul_time -= _dt;
    }
}

void EnemyEnt::attract_to(Vector2d _p)
{
    acc = (_p - pos).getNorm() * (ENEMY_ACC / (_p - pos).getAbs());
}

void EnemyEnt::hit()
{
    if (invul_time <= 0)
    {
        hit_points -= 1;
    }
}
