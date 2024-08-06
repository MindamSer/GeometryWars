#pragma once

#include "Entities.h"

class PlayerEnt : public SmartEnt
{
protected:
    float max_fire_cooldown;
    float fire_cooldown;

public:
    PlayerEnt(int _x, int _y, Polygon _sprite);
    PlayerEnt() = default;
    ~PlayerEnt() = default;

    float getMCD() const;
    void setMCD(float _mcd);
    float getCD() const;
    void setCD(float _cd);

    void update(float _dt, float _time);
    void lookAt(int _x, int _y);

    bool fire();
    bool hit();
    void lvl_up();
};



class EnemyEnt : public SmartEnt
{
protected:
    int max_hit_points;
    int hit_points;

public:
    EnemyEnt(int _x, int _y, Vector2d _vel, Polygon _sprite, int _lvl);
    EnemyEnt() = default;
    ~EnemyEnt() = default;

    int getMHP() const;
    void setMHP(int _mhp);
    int getHP() const;
    void setHP(int _hp);

    void update(float _dt, float _time);
    void attract_to(Vector2d _vel);

    void hit();
};



class BulletEnt : public StupidEnt
{
protected:

public:
    BulletEnt(Vector2d _pos, Vector2d _vel,
              float _phi, Polygon _sprite);
};



class ParticleEnt : public StupidEnt
{
protected:

public:
    ParticleEnt(Vector2d _pos, Vector2d _vel,
                float _phi, Polygon _sprite);

    void draw() const;
};



class BigBrother
{
private:
    Polygon playerSprite;
    Polygon enemySprite;
    Polygon bulletSprite;
    Polygon particleSprite;

    PlayerEnt player;
    bool player_alive;
    float respawn_delay;

    std::vector<EnemyEnt> enemies;
    std::vector<EnemyEnt> spawn_queue;
    float wave_delay;
    float enemies_delay;

    std::vector<BulletEnt> bullets;
    std::vector<ParticleEnt> particles;

    float time;
    int score;

    Vector2d upgrade;

public:
    BigBrother() = default;
    ~BigBrother() = default;

    void init();
    void step(float _dt);
    void over();

    void spawn_player();
    void spawn_bullets();
    void emit_particles(int _n,
                        Vector2d _pos, Vector2d _vel,
                        float _add_pos_l, float _add_vel_l);

    void update_all(float _dt);
    void draw_all() const;
};
