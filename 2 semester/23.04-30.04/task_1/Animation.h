#pragma once
#include<SFML/Graphics.hpp>

class Animation
{
private:
    sf::Sprite m_sprite;
    float m_frame, m_speed;
    std::vector<sf::IntRect> m_frames;
public:
    sf::Sprite& sprite() noexcept { return m_sprite; };

    Animation(sf::Texture& t, int x, int y, int w, int h, int count, float m_speed)
        :m_frame{ 0 }, m_speed{ m_speed }
    {

        for (int i = 0; i < count; i++)
            m_frames.push_back(sf::IntRect(x + i * w, y, w, h));

        m_sprite.setTexture(t);
        m_sprite.setOrigin(w / 2, h / 2);
        m_sprite.setTextureRect(m_frames[0]);
    }

    void update()
    {
        m_frame += m_speed;
        auto n = m_frames.size();
        if (m_frame >= n)
            m_frame -= n;
        if (n > 0)
            m_sprite.setTextureRect(m_frames[static_cast<int>(m_frame)]);
    }
public:
    const bool isEnd() const
    {
        return m_frame + m_speed >= m_frames.size();
    }

};
