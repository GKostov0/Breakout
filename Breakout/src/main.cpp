#include "Core\ResourcesProvider\ResourcesProvider.h"

#include <iostream>

int main()
{
	Shader sh = ResourcesProvider::LoadShader("Breakout//src//shaders//vertex.vs", "Breakout//src//shaders//fragment.frag", nullptr, "testShader");

	std::cin.get();
	return 0;
}