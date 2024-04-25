#include "Core\Shader\Shader.h"

#include <iostream>

int main()
{
	Shader sh;
	sh.Compile("Breakout//src//shaders//vertex.vs", "Breakout//src//shaders//fragment.frag");

	std::cin.get();
	return 0;
}