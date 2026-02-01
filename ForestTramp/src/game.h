#pragma once
#include <core/layer.h>
#include <DGGL/renderer.h>

class Game : DGE::Layer
{
private:
	void onAttach() override;
	void onUpdate() override;
	void onDetach() override;
	DGE::Renderer2D m_renderer;

public:
	Game();
	~Game();
};