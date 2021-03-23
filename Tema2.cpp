#include "Tema2.h"
#include "Object.h"
#include "Camera.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

//float FoV = 50, width = 5, height = 5;

int rand_gen(int n) {
	
	int randomNumbers[5];
	for (int i = 0; i < 5; i++) {
		randomNumbers[i] = (rand() % n) + 1;
	}

	return randomNumbers[rand() % 5];
}

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	srand((unsigned)time(0));
	time_no_red = Engine::GetElapsedTime();
	// The moving sphere
	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// The platform

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	//Platform 2.0
	{
		Mesh* platform = Object::CreatePlatform("platform", glm::vec3(0, 0, 0), 1, glm::vec3(1, 1, 1));
		meshes[platform->GetMeshID()] = platform;
	}

	// Energy bar
	Mesh* energyBar = Object::CreatePowerBar("energyBar", 3, glm::vec3(0, 1, 0));

	// Create a shader program for drawing face polygon
	{
		Shader* shader = new Shader("ShaderTema2");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Camera
	renderCameraTarget = false;
	camera = new Camera();
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{



	// Render platforms
	glm::mat4 modelMatrix = glm::mat4(1);
	for (int i = 0; i < 11; i++) {
		modelMatrix = glm::mat4(1);
		glm::vec3 aux_color;

		if (!colored1[i]) {
			if (rand_gen(5) == 4) {
				int c = rand_gen(5) - 1;
				time_red = Engine::GetElapsedTime();
				while (c == 0 && time_red - time_no_red < 3) {
					c = rand_gen(5) - 1;
				}

				platform1_colors[i] = colors[c];
				colored1[i] = true;
			}
			else {
				platform1_colors[i] = colors[4];
			}
		}
		if (!colored2[i]) {
			if (rand_gen(5) == 4) {
				int c = rand_gen(5) - 1;
				time_red = Engine::GetElapsedTime();
				while (c == 0 && time_red - time_no_red < 3) {
					c = rand_gen(5) - 1;
				}

				platform2_colors[i] = colors[c];
				colored2[i] = true;
			}
			else {
				platform1_colors[i] = colors[4];
			}
		}
		if (!colored3[i]) {
			if (rand_gen(5) == 4) {
				int c = rand_gen(5) - 1;
				time_red = Engine::GetElapsedTime();
				while (c == 0 && time_red - time_no_red < 3) {
					c = rand_gen(5) - 1;
				}

				platform3_colors[i] = colors[c];
				colored3[i] = true;
			}
			else {
				platform1_colors[i] = colors[4];
			} 
		}

		// Platform 2
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5, 0, z[i] + length));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1, 1.25));
		bool intersect_center = Object::intersect(ballX, ballY, 0, -0.5, 0, 1.25 * (z[i] + length), 0.5, 0.1, 1.25 + 1.25 * (z[i] + length), 0.125);


		RenderSimpleMesh(meshes["platform"], shaders["ShaderTema2"], 0, modelMatrix, platform2_colors[i]);
		if (intersect_center) {
			if (platform2_colors[i] == glm::vec3(1, 0, 0)) {
				
				cout << "exit from red2\n";// red
				exit(-1);
			}
			else if (platform2_colors[i] == glm::vec3(1, 1, 0)) {
				energyX -= 0.1;	// yellow
			}
			else if (platform2_colors[i] == glm::vec3(1, 0.6, 0)) {
				speed_blocked = true;	// orange
				platform_speed = 6;
				deform = true;
				time1 = Engine::GetElapsedTime();
				time3 = Engine::GetElapsedTime();
				//timer
			}
			else if (platform2_colors[i] == glm::vec3(0, 1, 0)) {
				if (energyX + 0.2 < 1) energyX += 0.2;	// green
				else energyX = 1;
				deform = true;
				time1 = Engine::GetElapsedTime();
			}
			platform2_colors[i] = colors[5];
		}


		// Platform 1
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0, 0));
		RenderSimpleMesh(meshes["platform"], shaders["ShaderTema2"], 0, modelMatrix, platform1_colors[i]);

		bool intersect_left = Object::intersect(ballX, ballY, 0, -2.5, 0, 1.25 * (z[i] + length), -1.5, 0.1, 1.25 + 1.25 * (z[i] + length), 0.125);
		if (intersect_left) {
			if (platform1_colors[i] == glm::vec3(1, 0, 0)) {
				
				cout << "exit from red1\n";// red
				exit(-1);
			}
			else if (platform1_colors[i] == glm::vec3(1, 1, 0)) {
				energyX -= 0.1;	// yellow
			}
			else if (platform1_colors[i] == glm::vec3(1, 0.6, 0)) {
				speed_blocked = true;	// orange
				platform_speed = 6;
				deform = true;
				time1 = Engine::GetElapsedTime();
				time3 = Engine::GetElapsedTime();
				//timer
			}
			else if (platform1_colors[i] == glm::vec3(0, 1, 0)) {
				if (energyX + 0.2 < 1) energyX += 0.2;	// green
				else energyX = 1;
				deform = true;
				time1 = Engine::GetElapsedTime();
			}

			platform1_colors[i] = glm::vec3(1, 0, 1);
		}



		// Platform 3
		modelMatrix = glm::translate(modelMatrix, glm::vec3(4, 0, 0));
		RenderSimpleMesh(meshes["platform"], shaders["ShaderTema2"], 0, modelMatrix, platform3_colors[i]);

		bool intersect_right = Object::intersect(ballX, ballY, 0, 1.5, 0, 1.25 * (z[i] + length), 2.5, 0.1, 1.25 + 1.25 * (z[i] + length), 0.125);
		if (intersect_right) {
			if (platform3_colors[i] == glm::vec3(1, 0, 0)) {
				cout << "exit from red3\n";// red
				exit(-1);
				
			}
			else if (platform3_colors[i] == glm::vec3(1, 1, 0)) {
				energyX -= 0.1;	// yellow
			}
			else if (platform3_colors[i] == glm::vec3(1, 0.6, 0)) {
				speed_blocked = true;	// orange
				platform_speed = 6;
				deform = true;
				time1 = Engine::GetElapsedTime();
				time3 = Engine::GetElapsedTime();
				//timer
			}
			else if (platform3_colors[i] == glm::vec3(0, 1, 0)) {
				if (energyX + 0.2 < 1) energyX += 0.2;	// green
				else energyX = 1;
				deform = true;
				time1 = Engine::GetElapsedTime();
			}

			platform3_colors[i] = colors[5];
		}


		if (z[i] + length > 2.6) {
			z[i] -= 12.5;
			colored1[i] = false;
			colored2[i] = false;
			colored3[i] = false;
		}
	}
	if(start) length += platform_speed * deltaTimeSeconds;



	//Render sphere
	if(ballY >= 0.2 || ((-2.3 <= ballX && ballX <= -1.5) || (-0.4 <= ballX && ballX <= 0.4) || (1.5 <= ballX && ballX <= 2.3))) 
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(ballX, ballY, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], deform, modelMatrix, ball_color);
	}
	else {
		if (ballY > -3) {
			ballY -=  4 * deltaTimeSeconds;
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(ballX, ballY, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25));
			RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], deform, modelMatrix, ball_color);
			cout << ballY << endl;
		}
		if (ballY <= -1) {
			// game over
			cout << "game over\n";
			exit(-1);
			
		}
	}




	// Energy bar
	modify_energy = false;
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(3, 4.5, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(1.5, 0.2, 0.01));
	RenderSimpleMesh(meshes["platform"], shaders["VertexColor"], deform, modelMatrix, glm::vec3(1, 1, 1));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0.1));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(energyX, 1, 1));
	RenderSimpleMesh(meshes["platform"], shaders["VertexNormal"], deform, modelMatrix, glm::vec3(0, 1, 0));
	modify_energy = true;

	//Jump
	if (jump) {
		if (ballY < 1) {
			ballY += 1.5 * deltaTimeSeconds;
		}
		if (ballY >= 1) {
			jump = false;
		}
	}
	else {
		if (ballY > 0.2) {
			ballY -= 1.5 * deltaTimeSeconds;
		}
	}

	if(start) energyX -= 0.02 * deltaTimeSeconds;
	if (energyX <= 0) {
		cout << "no energy left\n";
		exit(-1);
	}
	generate = (generate + 1) % 3;

	time2 = Engine::GetElapsedTime();
	if (time2 - time1 > 3) {
		deform = false;
	}
	if (time2 - time3 > 3 && speed_blocked) {
		speed_blocked = false;
		platform_speed = 2.5;
	}
}

void Tema2::FrameEnd()
{
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, int deform, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// Render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Set eye position (camera position) uniform
	glm::vec3 eyePosition = camera->position;
	glUniform3fv(glGetUniformLocation(shader->program, "eye_position"), 1, glm::value_ptr(eyePosition));

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix 
	if (modify_energy) {
		glm::mat4 viewMatrix = camera->GetViewMatrix();
		int loc_view_matrix = glGetUniformLocation(shader->program, "View");
		glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	}
	else {
		glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0, 2, 5), glm::vec3(0, 2, 4), glm::vec3(0, 1, 0));
		int loc_view_matrix = glGetUniformLocation(shader->program, "View");
		glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	}
	

	// Bind projection matrix
	//glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	//Bind deform values
	if (deform == 1) {
		int deformation = glGetUniformLocation(shader->program, "deform");
		glUniform1i(deformation, deform);

		glm::vec2 resolution = window->GetResolution();
		int res_location = glGetUniformLocation(shader->program, "u_resolution");
		glUniform2fv(res_location, 1, glm::value_ptr(resolution));

		int time = glGetUniformLocation(shader->program, "time");
		glUniform1f(time, Engine::GetElapsedTime());
	}
	else {
		int deformation = glGetUniformLocation(shader->program, "deform");
		glUniform1i(deformation, deform);
	}

	// Set ball color
	//glm::vec3 ballColor = glm::vec3(1, 0, 1);
	glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(color));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	float speed = 2;

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		/*glm::vec3 up = glm::vec3(0, 1, 0);
		glm::vec3 right = GetSceneCamera()->transform->GetLocalOXVector();
		glm::vec3 forward = GetSceneCamera()->transform->GetLocalOZVector();
		forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));*/
		if (speed_blocked) {
			speed_blocked = false;
			platform_speed = 2.5;
		}
	}

	if (window->KeyHold(GLFW_KEY_W)) {
		if (platform_speed < 7 && !speed_blocked) {
			platform_speed += 2 * deltaTime;
			cout << platform_speed << endl;
		}
			
	}
	if (window->KeyHold(GLFW_KEY_S && !speed_blocked)) {
		if (platform_speed > 1)
			platform_speed -= 2 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_A)) {
			ballX -= 1.7 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_D)) {
		ballX += 1.7 * deltaTime;
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE && ballY <= 0.25)
		jump = true;

	if (key == GLFW_KEY_C) {
		if (key_c == false) key_c = true;
		else key_c = false;
	}

	if (key == GLFW_KEY_P)
		start = (start + 1) % 2;
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (!key_c) {
			renderCameraTarget = false;
			// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(-deltaY * sensivityOX);
			camera->RotateFirstPerson_OY(-deltaX * sensivityOY);
		}

		if (key_c) {
			renderCameraTarget = true;
			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(-deltaY * sensivityOX);
			camera->RotateThirdPerson_OY(-deltaX * sensivityOY);
		}

	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}