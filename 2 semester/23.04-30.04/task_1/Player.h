#pragma once
#include"Entity.h"

class Player : public Entity
{
private:
	constexpr static int max_speed = 15;
	constexpr static float thrust_coeff = 0.99f;
private:
	bool m_thrust;
	int m_score;
public:
	Player(Animation& a, int HP, float x, float y, float dx, float dy, float angle, float radius)
		: Entity(EntityType::Player, a, HP, x, y, dx, dy, angle, radius), m_score{ 0 }, m_thrust{ false }
	{}

	std::size_t get_score() const noexcept { return m_score; };
	void set_score(std::size_t score) noexcept { m_score = score; };

	bool get_thrust() const noexcept { return m_thrust; };
	void set_thrust(bool thrust) noexcept { m_thrust = thrust; };

	bool is_alive() const noexcept { return (m_HP > 0); }

	void score_increase() noexcept { ++m_score; }


private:
	void virtual update(std::size_t win_width, std::size_t win_height) override
	{
		if (m_thrust)
		{
			m_dx += std::cos(m_angle * Dectorad) * 0.2;
			m_dy += std::sin(m_angle * Dectorad) * 0.2;
		}
		else
		{
			m_dx *= thrust_coeff;
			m_dy *= thrust_coeff;
		}

		float m_speed = std::sqrt(m_dx * m_dx + m_dy * m_dy);
		if (m_speed > max_speed)
		{
			m_dx *= max_speed / m_speed;
			m_dy *= max_speed / m_speed;
		}

		m_x += m_dx;
		m_y += m_dy;

		if (m_x > win_width) m_x = 0; if (m_x < 0) m_x = win_width;
		if (m_y > win_height) m_y = 0; if (m_y < 0) m_y = win_height;
	}

};

