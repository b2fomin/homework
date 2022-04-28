#pragma once
#include"Entity.h"

class Asteroid : public Entity
{
private:
    constexpr static int max_speed = 4;
public:
    Asteroid(Animation& a, float x = 0.f, float y = 0.f, float angle = 0.f, float radius = 1.f)
        : Entity(EntityType::Asteroid, a, 1, x, y, 0, 0, angle)
    {
        std::random_device rd;
        std::default_random_engine gen{rd()};
        std::uniform_int_distribution<int> speed_distribution
        (-max_speed, max_speed);
        m_dx = speed_distribution(gen);
        m_dy = speed_distribution(gen);
    }
private:
    void virtual update() override
    {
        m_x += m_dx;
        m_y += m_dy;

        if (m_x > W) m_x = 0;  if (m_x < 0) m_x = W;
        if (m_y > H) m_y = 0;  if (m_y < 0) m_y = H;
    }

};
