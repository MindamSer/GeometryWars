#include "GameClasses.h"

//BigBrother functions --------------------------------

void BigBrother::init()
{
    playerSprite =   load_poly("./assets/player_polygon");
    enemySprite =    load_poly("./assets/enemy_polygon");
    bulletSprite =   load_poly("./assets/bullet_polygon");
    particleSprite = load_poly("./assets/particle_polygon");

    player_alive = false;
    respawn_delay = 0;

    wave_delay = WAVE_DELAY;
    enemies_delay = WAVE_ENEMIES_DELAY;

    upgrade = Vector2d(-OFF_SCREEN_COORD, -OFF_SCREEN_COORD);
}

void BigBrother::step(float _dt)
{
    if (!player_alive)
    {
        if (respawn_delay > 0)
        {
            respawn_delay -= _dt;
        }
        else
        {
            spawn_player();
            respawn_delay = PLAYER_RESPAWN_TIME;
            player_alive = true;
        }
    }
    else
    {
        time += _dt;
    }

    if ((wave_delay > 0) && (enemies.size() == 0) && (spawn_queue.size() == 0))
    {
        wave_delay -= _dt;
    }
    if (wave_delay <= 0)
    {
        wave_delay = WAVE_DELAY;

        int n = 5 + player.getLV() * WAVE_ENEMY_PER_LVL + int(time) / 60;
        int d = (SCREEN_HEIGHT - WAVE_OFF_WALL * 2) / (n - 1);
        float o = (2 * M_PI) / n;
        int lv = rand() % 3 + 1;
        int wt = rand() % 3 + 1;

        switch(wt)
        {
            case 1:
                for (int i = 0; i < n; i++)
                {
                    spawn_queue.push_back(EnemyEnt(SCREEN_WIDTH / 2 + ((i % 2) * 2 - 1) * (SCREEN_WIDTH / 2 - WAVE_OFF_WALL),
                                                   WAVE_OFF_WALL + d * i, -Vector2d(((i % 2) * 2 - 1) * WAVE_VELOCITY, 0), enemySprite, lv));
                }
                break;

            case 2:
                for (int i = 0; i < n; i++)
                {
                    spawn_queue.push_back(EnemyEnt(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
                                                   Matrix2d(i * o) * Vector2d(WAVE_VELOCITY, 0),
                                                   enemySprite, lv));
                }
                break;

            case 3:
                for (int i = 0; i < n; i++)
                {
                    spawn_queue.push_back(EnemyEnt(WAVE_OFF_WALL + rand() % (SCREEN_WIDTH - WAVE_OFF_WALL * 2),
                                                   WAVE_OFF_WALL + rand() % (SCREEN_HEIGHT - WAVE_OFF_WALL * 2),
                                                   Matrix2d(float(rand() % 360) / 360 * 2 * M_PI) * Vector2d(WAVE_VELOCITY, 0),
                                                   enemySprite, lv));
                }
                break;
        }
    }
    if (spawn_queue.size() != 0)
    {
        if (enemies_delay > 0)
        {
            enemies_delay -= _dt;
            emit_particles(PARTICLES_SPAWN,
                           spawn_queue[0].getPos(), Vector2d(),
                           spawn_queue[0].getRad(), -PARTICLES_SPAWN_SPRAY);
        }
        else
        {
            enemies_delay = WAVE_ENEMIES_DELAY;
            enemies.push_back(spawn_queue[0]);
            spawn_queue.erase(spawn_queue.begin());
        }
    }

    player.setAcc(get_control() * PLAYER_ACC);
    player.lookAt(get_cursor_x(), get_cursor_y());
    if (is_mouse_button_pressed(0) && player.fire())
    {
        spawn_bullets();
    }

    update_all(_dt);
}

void BigBrother::over()
{
    return;
}

void BigBrother::spawn_player()
{
    player = PlayerEnt(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, playerSprite);
    time = 0;
    score = 0;
}

void BigBrother::spawn_bullets()
{
    float phi = player.getPhi();
    float r = player.getRad();
    Vector2d bulvel = Matrix2d(phi) * Vector2d(BULLET_SPEED, 0);

    Vector2d bul1pos = Vector2d(BULLET_SPAWN_Z,0);
    Vector2d bul2pos = Vector2d(BULLET_SPAWN_X,0) + Vector2d(0,BULLET_SPAWN_Y);
    Vector2d bul3pos = Vector2d(BULLET_SPAWN_X,0) - Vector2d(0,BULLET_SPAWN_Y);

    BulletEnt bul1(player.getPos() + Matrix2d(phi) * bul1pos * r,
                   bulvel, phi, bulletSprite);
    BulletEnt bul2(player.getPos() + Matrix2d(phi) * bul2pos * r,
                   bulvel, phi, bulletSprite);
    BulletEnt bul3(player.getPos() + Matrix2d(phi) * bul3pos * r,
                   bulvel, phi, bulletSprite);

    if (player.getLV() != 2)
    {
        bullets.push_back(bul1);
        emit_particles(PARTICLES_GUN,
                       bul1.getPos(), bulvel,
                       PARTICLES_GUN_WIDTH, PARTICLES_GUN_SPRAY);
    }
    if (player.getLV() > 1)
    {
        bullets.push_back(bul2);
        bullets.push_back(bul3);
        emit_particles(PARTICLES_GUN,
                       bul2.getPos(), bulvel,
                       PARTICLES_GUN_WIDTH, PARTICLES_GUN_SPRAY);
        emit_particles(PARTICLES_GUN,
                       bul3.getPos(), bulvel,
                       PARTICLES_GUN_WIDTH, PARTICLES_GUN_SPRAY);
    }
}

void BigBrother::emit_particles(int _n,
                                Vector2d _pos, Vector2d _vel,
                                float _add_pos_l, float _add_vel_l)
{
    float add_pos_phi;
    float add_vel_phi;
    for (int i = 0; i < _n; i++)
    {
        add_pos_phi = float(rand() % 360) / 360 * 2 * M_PI;
        add_vel_phi = float(rand() % 360) / 360 * 2 * M_PI;

        Vector2d add_pos = Matrix2d(add_pos_phi) *
        Vector2d(_add_pos_l, 0) * (float(rand() % 100) / 100);
        Vector2d add_vel = Matrix2d(add_vel_phi) *
        Vector2d(_add_vel_l, 0) * (float(rand() % 100) / 100);

        particles.push_back(ParticleEnt(_pos + add_pos, _vel + add_vel,
                                        -(_vel + add_vel).getArg(), particleSprite));
    }
}

void BigBrother::update_all(float _dt)
{
    player.update(_dt, time);

    emit_particles(PARTICLES_UPGRADE,
                   upgrade, Vector2d(),
                   player.getRad() / 2, PARTICLES_UPGRADE);

    if ((player.getPos() - upgrade).getAbs() < player.getRad() * UPGRADE_RAD)
    {
        upgrade = Vector2d(-OFF_SCREEN_COORD, -OFF_SCREEN_COORD);
        player.lvl_up();
        score += 100;
    }

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].attract_to(player.getPos());

        enemies[i].update(_dt, time);

        if (collision(enemies[i], player))
        {
            player.hit();
        }
        if (enemies[i].getHP() < 1)
        {
            if (rand() % 100 < UPGRADE_PROB)
            {
                upgrade = enemies[i].getPos();
            }

            emit_particles(PARTICLES_ENEMY,
                           enemies[i].getPos(), enemies[i].getVel(),
                           enemies[i].getRad(), enemies[i].getRad() *
                           PARTICLES_ENEMY_SPRAY);
            score += enemies[i].getMHP();
            enemies.erase(std::next(enemies.begin(), i));
            i--;
        }
    }

    if (player.getLV() < 1)
    {
        emit_particles(PARTICLES_PLAYER,
                       player.getPos(), player.getVel(),
                       player.getRad(), player.getRad() *
                       PARTICLES_PLAYER_SPRAY);
        player_alive = false;
        player = PlayerEnt(SCREEN_WIDTH * 3, SCREEN_HEIGHT * 3, playerSprite);
    }

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].update(_dt, time);

        for (int j = 0; j < enemies.size(); j++)
        {
            if (collision(bullets[i], enemies[j]))
            {
                bullets[i].setTTL(-1);
                enemies[j].hit();
            }
        }
        if (bullets[i].getTTL() <= 0)
        {
            emit_particles(PARTICLES_BULLET,
                           bullets[i].getPos(), bullets[i].getVel(),
                           bullets[i].getRad(), bullets[i].getRad()*
                           PARTICLES_BULLET_SPRAY);
            bullets.erase(std::next(bullets.begin(), i));
            i--;
        }

    }

    for (int i = 0; i < particles.size(); i++)
    {
        particles[i].update(_dt, time);

        if (particles[i].getTTL() <= 0)
        {
            particles.erase(std::next(particles.begin(), i));
            i--;
        }
    }
}

void BigBrother::draw_all() const
{
    player.draw();

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].draw();
    }
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].draw();
    }
    for (int i = 0; i < particles.size(); i++)
    {
        particles[i].draw();
    }

    char text[32];
    sprintf(text, "score:%d", score);
    draw_text(8, 760, text, 3);
    sprintf(text, "%02d:%02d.%03d", int(time) / 60, int(time) % 60, int(time * 1000) % 1000);
    draw_text(8, 760-27, text, 3);
}
