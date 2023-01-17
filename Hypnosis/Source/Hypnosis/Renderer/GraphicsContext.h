#pragma once

namespace Hypnosis {

	class GraphicsContext
	{
	public:
		virtual bool Init() = 0;
		virtual void SwapBuffers() = 0;

	};

}