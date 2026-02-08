#pragma once
#include "dge.h"
#include "core/event.h"

namespace DGE
{
	class Layer
	{
	public:
		Layer() {};
		virtual void onAttach() = 0;
		virtual void onUpdate() = 0;
		virtual void onEvent(Event& e) {};
		virtual void onDetach() {}

	protected:
		void setName(std::string name)
		{
			this->layername = name;
		}

		std::string layername;
	private:

	};
}