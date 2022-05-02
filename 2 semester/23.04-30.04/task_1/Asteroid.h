#pragma once
#include"Entity.h"

class Asteroid : public Entity
{
private:
    constexpr static int max_speed = 4;
public:
    Asteroid(Animation& a, std::size_t win_width, std::size_t win_height, float radius)
        : Entity(EntityType::Asteroid, a, 1, 0.f, 0.f, 0.f, 0.f, 0.f, radius)
    {
        std::random_device rd;
        std::default_random_engine gen{rd()};
        std::uniform_int_distribution<int> x_dist(0, win_width);
        std::uniform_int_distribution<int> y_dist(0, win_height);
        std::uniform_int_distribution<int> angle_dist(0, 360);
        std::uniform_int_distribution<int> speed_dist
        (-max_speed, max_speed);
        m_dx = speed_dist(gen);
        m_dy = speed_dist(gen);
        m_x = x_dist(gen);
        m_y = y_dist(gen);
        m_angle = angle_dist(gen);
    }

    Asteroid(Animation& a, float x, float y, float angle, float radius)
        : Entity(EntityType::Asteroid, a, 1, x, y, 0.f, 0.f, angle, radius)
    {
        std::random_device rd;
        std::default_random_engine gen{ rd() };
        std::uniform_int_distribution<int> speed_dist
        (-max_speed, max_speed);
        m_dx = speed_dist(gen);
        m_dy = speed_dist(gen);
    }
private:
    void virtual update(std::size_t win_width, std::size_t win_height) override
    {
        m_x += m_dx;
        m_y += m_dy;

        if (m_x > win_width) m_x = 0;  if (m_x < 0) m_x = win_width;
        if (m_y > win_height) m_y = 0;  if (m_y < 0) m_y = win_height;
    }

};
