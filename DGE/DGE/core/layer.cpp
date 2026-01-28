#include "layer.h"

namespace DGE
{
	Layer::Layer()
	{
	}

	void Layer::onDetach()
	{
	}

	void Layer::setName(std::string name)
	{
		this->layername = name;
	}
}