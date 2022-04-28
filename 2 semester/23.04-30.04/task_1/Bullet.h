#pragma once
#include"Entity.h"

class Bullet : public Entity
{
private:
	constexpr static int max_speed = 6;
public:
	Bullet(Animation& a, float x = 0.f, float y = 0, float dx = 0.f, float dy = 0.f, float angle = 0.f, float radius = 1.f)
		: Entity(EntityType::Bullet, a, 1, x, y, dx, dy, angle)
	{}
private:
	void virtual update() override
	{
		m_dx = std::cos(m_angle * Dectorad) * max_speed;
		m_dy = std::sin(m_angle * Dectorad) * max_speed;
		// angle+=rand()%7-3;  /*try this*/
		m_x += m_dx;
		m_y += m_dy;

		if (m_x > W || m_x<0 || m_y>H || m_y < 0) m_HP = 0;
	}

};
