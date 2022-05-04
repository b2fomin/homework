#pragma once

#include <iomanip>
#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "calculator.hpp"
#include "view.hpp"

class Visualizer
{
public:

	Visualizer(std::size_t width, std::size_t height, std::complex<float> c) :
		m_window(sf::VideoMode(width, height), "MANDELBROT VISUALIZER", sf::Style::Close),
		m_calculator(m_window.getSize().x, m_window.getSize().y, 100U, c), m_need_redraw(true),
		m_view(sf::Vector2f(0.0f, 0.0f), 6.0f, 6.0f / (m_calculator.width() / m_calculator.height()))
	{
		initialize();
	}

	~Visualizer() noexcept = default;

private:

	void initialize();

public:

    void run();

private:

    void review();
    void update();
    void render();

private:

    void handle_key_pressed(sf::Keyboard::Key, sf::Keyboard::Key&);

private:

    sf::RenderWindow m_window;
    sf::Image        m_image;
    sf::Sprite       m_sprite;
    sf::Texture      m_texture;
    sf::Font         m_font;
    sf::Text         m_text;

    Calculator m_calculator;

	bool m_need_redraw;

    View m_view;

    std::vector < sf::Color > m_colors;
};