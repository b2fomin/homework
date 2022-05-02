#pragma once
#include"Animation.h"
#include"include_common.h"

class Entity
{
public:
protected:
	Animation m_anim;
	float m_x, m_y, m_dx, m_dy, m_r, m_angle;
	int m_HP;
	EntityType m_type;
public:
	Entity(EntityType type, Animation& a, int HP, float x, float y,
		float dx, float dy, float Angle, float radius)
		: m_type{ type }, m_HP{HP}, m_anim{ a }, m_x{ x }, m_y{ y }, m_dx{ dx }, m_dy{ dy }, m_angle{ Angle }, m_r{ radius }
	{}

	// можно применить идиому NVI, или шаблонный метод для гибкости
	virtual void update(std::size_t win_width, std::size_t win_height) {}; // = default

	EntityType virtual get_type() const noexcept { return m_type; };
	virtual const std::size_t& get_HP() const noexcept { return m_HP; };
	virtual const float& get_x() const noexcept { return m_x; };
	virtual const float& get_y() const noexcept { return m_y; };
	virtual const float& get_angle() const noexcept { return m_angle; };
	virtual const float& get_r() const noexcept { return m_r; };
	virtual Animation& get_anim() noexcept { return m_anim; };

	virtual void set_HP(std::size_t HP) noexcept { m_HP = HP; };
	virtual void set_angle(float angle) noexcept { m_angle = angle; };
	virtual void set_anim(Animation& anim) noexcept { m_anim = anim; };

	void draw(sf::RenderWindow& app)
	{
		m_anim.sprite().setPosition(m_x, m_y);
		m_anim.sprite().setRotation(m_angle + 90);
		app.draw(m_anim.sprite());
	}

	virtual ~Entity() = default;

	static bool isCollide(std::shared_ptr<Entity>& a, std::shared_ptr<Entity>& b)
	{
		return pow((b->m_x - a->m_x), 2)+
			pow((b->m_y - a->m_y), 2) <
			2*pow((a->m_r + b->m_r), 2);
	}
};