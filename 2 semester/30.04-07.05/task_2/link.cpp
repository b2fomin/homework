#include "link.hpp"

void Link::update() const
{
	const auto delta = m_particle_2->position() - m_particle_1->position();
	const float A = 0.01f;

	auto force = norm(delta) * static_cast<float>(A * (length(delta)-m_distance));

	m_particle_1->move(force);
	m_particle_2->move(-force);
}