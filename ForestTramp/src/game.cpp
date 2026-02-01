#include "game.h"
#include <iostream>

Game::Game()
{

}

Game::~Game()
{

}

void Game::onAttach()
{
	m_renderer.init();
	std::cout << "Game attached" << std::endl;
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "GL ERROR: " << err << std::endl;
}

void Game::onUpdate()
{
	m_renderer.beginBatch();
	m_renderer.addRect(0.f, 0.f, 10.2f, 10.2f, 255, 0, 0, 255);
	m_renderer.addRect(20.f, 0.f, 10.2f, 10.2f, 255, 255, 0, 255);
	m_renderer.addRect(0.f, 20.f, 10.2f, 10.2f, 255, 0, 255);
	m_renderer.addRect(20.f, 20.f, 10.2f, 10.2f, 0, 255, 0);
	m_renderer.renderBatch();

}

void Game::onDetach()
{

}