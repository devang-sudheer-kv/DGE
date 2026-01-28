#pragma once
#include "dge.h"

namespace DGE
{
	class Layer
	{
	public:
		Layer();
		virtual void onAttach() = 0;
		virtual void onUpdate() = 0;
		virtual void onDetach();
	protected:
		void setName(std::string name);

		std::string layername;
	private:

	};
}