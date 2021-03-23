#include "Object.h"

#include <Core/Engine.h>

Mesh* Object::CreatePlatform(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color) {

	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(0, 0, 1), color),
		VertexFormat(corner + glm::vec3(1, 0, 1), color),
		VertexFormat(corner + glm::vec3(0, 1, 1), color),
		VertexFormat(corner + glm::vec3(1, 1, 1), color),
		VertexFormat(corner + glm::vec3(0, 0, 0), color),
		VertexFormat(corner + glm::vec3(1, 0, 0), color),
		VertexFormat(corner + glm::vec3(0, 1, 0), color),
		VertexFormat(corner + glm::vec3(1, 1, 0), color),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,	// indices for first triangle
		1, 3, 2,
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4
		// indices for second triangle
		// TODO: Complete indices data
	};

	Mesh* cube = new Mesh(name);

	cube->InitFromData(vertices, indices);
	return cube;
}

Mesh* Object::CreatePowerBar(std::string name, float length, glm::vec3 color) {
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(length, 0, 0), color),
		VertexFormat(glm::vec3(0, -length / 5, 0), color),
		VertexFormat(glm::vec3(length, -length / 5, 0), color),
	};

	std::vector<unsigned short> indices
	{
		0, 1, 2,
		1, 3, 2
	};

	Mesh* bar = new Mesh(name);

	bar->SetDrawMode(GL_TRIANGLES);

	bar->InitFromData(vertices, indices);
	return bar;
}

bool Object::intersect(float sphereX, float sphereY, float sphereZ,
	float boxMinX, float boxMinY, float boxMinZ,
	float boxMaxX, float boxMaxY, double boxMaxZ, float radius) {

	double x = max(boxMinX, min(sphereX, boxMaxX));
	double y = max(boxMinY, min(sphereY, boxMaxY));
	double z = max(boxMinZ, min(sphereZ, boxMaxZ));

	double distance = sqrt((x - sphereX) * (x - sphereX) +
							(y - sphereY) * (y - sphereY) +
							(z - sphereZ) * (z - sphereZ));

	return distance < radius;
}
