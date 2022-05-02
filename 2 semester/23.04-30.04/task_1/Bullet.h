#pragma once
#include"Entity.h"

class Bullet : public Entity
{
private:
	constexpr static int max_speed = 6;
public:
	Bullet(Animation& a, float x, float y, float dx, float dy, float angle, float radius)
		: Entity(EntityType::Bullet, a, 1, x, y, dx, dy, angle, radius)
	{}
private:
	void virtual update(std::size_t win_width, std::size_t win_height) override
	{
		m_dx = std::cos(m_angle * Dectorad) * max_speed;
		m_dy = std::sin(m_angle * Dectorad) * max_speed;
		// angle+=rand()%7-3;  /*try this*/
		m_x += m_dx;
		m_y += m_dy;

		if (m_x > win_width || m_x < 0 || m_y > win_height || m_y < 0) m_HP = 0;
	}

};
