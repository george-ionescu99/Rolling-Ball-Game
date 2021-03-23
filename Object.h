#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object
{
	Mesh* CreatePlatform(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);
	Mesh* CreatePowerBar(std::string name, float length, glm::vec3 color);
	bool intersect(float sphereX, float sphereY, float sphereZ,
		float boxMinX, float boxMinY, float boxMinZ,
		float boxMaxX, float boxMaxY, double boxMaxZ, float radius);
}