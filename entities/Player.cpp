#include "GameClasses.h"

//PlayerEnt functions --------------------------------

PlayerEnt::PlayerEnt(int _x, int _y, Polygon _sprite)
: SmartEnt(Vector2d(_x, _y), Vector2d(),
           0., _sprite,
           1, PLAYER_MAX_SPEED,
           PLAYER_INVUL, PLAYER_BLINK_FREQ)
{
    max_fire_cooldown = PLAYER_FIRE_CD;
    fire_cooldown = max_fire_cooldown;
}

float PlayerEnt::getMCD() const
{
    return max_fire_cooldown;
}

void PlayerEnt::setMCD(float _mcd)
{
    max_fire_cooldown = _mcd;
}

float PlayerEnt::getCD() const
{
    return fire_cooldown;
}

void PlayerEnt::setCD(float _cd)
{
    fire_cooldown = _cd;
}

void PlayerEnt::update(float _dt, float _time)
{
    vel = vel + (acc - vel * PLAYER_DEACC_K) * _dt;
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

    if (fire_cooldown > 0)
    {
        fire_cooldown -= _dt;
    }
    if (invul_time > 0)
    {
        invul_time -= _dt;
    }
}

void PlayerEnt::lookAt(int _x, int _y)
{
    phi = -(Vector2d(_x, SCREEN_HEIGHT - _y) - pos).getArg();
}

bool PlayerEnt::fire()
{
    if (fire_cooldown <= 0)
    {
        fire_cooldown = max_fire_cooldown;
        return true;
    }
    return false;
}

bool PlayerEnt::hit()
{
    if (invul_time <= 0)
    {
        level--;
        invul_time = max_invul_time;
        return true;
    }
    return false;
}

void PlayerEnt::lvl_up()
{
    if (level < 3)
    {
        level++;
    }
}
