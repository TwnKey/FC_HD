#pragma once
#include <string>

#include <d3d9/d3d9.h>
#include <d3d9/d3dx9.h>
#include <unordered_set>
#include "Utilities.h"
/*It is a simple single threaded texture injector
based on SpecialK texture injection (Hooking CreateTextureFromFileFromMemory)
*/


class TextureInjector
{
	public:
		TextureInjector();
		~TextureInjector();
		std::unordered_set<std::string> injectable_textures;
		bool listAllTextures();
		bool Init();
		void * pool; 
		
		size_t size_pool;
};

