#pragma once

#include "Utils.h"
#include "Settings.h"

class Entity
{
protected:
    Vector2d pos;
    Vector2d vel;
    Vector2d acc;

    float phi;
    float omega;
    Polygon sprite;

public:
    Entity(Vector2d _pos, Vector2d _vel, Vector2d _acc,
           float _phi, float _omega, Polygon _sprite);
    Entity() = default;
    ~Entity() = default;

    Vector2d getPos() const;
    void setPos(Vector2d _pos);
    Vector2d getVel() const;
    void setVel(Vector2d _vel);
    Vector2d getAcc() const;
    void setAcc(Vector2d _acc);

    float getPhi() const;
    void setPhi(float _phi);
    float getOmega() const;
    void setOmega(float _omega);
    Polygon getSprite() const;
    void setSprite(Polygon _sprite);

    uint32_t getColor() const;
    void setColor(uint32_t _color);
    float getRad() const;
    void setRad(float _rad);

    void draw() const;
    void update(float _dt, float _time);
};

bool collision(const Entity &left, const Entity &right);



class SmartEnt : public Entity
{
protected:
    float max_speed;

    float max_invul_time;
    float invul_time;
    int blink_freq;

    int level;

public:
    SmartEnt(Vector2d _pos, Vector2d _vel,
             float _omega, Polygon _sprite,
             int _lvl, float _max_speed,
             float _max_invul_time, int _blink_freq);
    SmartEnt() = default;
    ~SmartEnt() = default;

    float getMaxSp() const;
    void setMaxSp(float _ms);
    float getMIT() const;
    void setMIT(float _mit);
    float getIT() const;
    void setIT(float _it);
    int getLV() const;
    void setLV(int _lvl);

    void draw() const;
    void update(float _dt, float _time);
};



class StupidEnt : public Entity
{
protected:
    float ttl;

public:
    StupidEnt(Vector2d _pos, Vector2d _vel,
              float _phi, Polygon _sprite,
              float _ttl);
    StupidEnt() = default;
    ~StupidEnt() = default;

    float getTTL() const;
    void setTTL(float _ttl);

    void update(float _dt, float _time);
};
