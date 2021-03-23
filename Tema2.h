#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>
#include "Camera.h"

class Tema2 : public SimpleScene
{
	public:
		Tema2();
		~Tema2();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderSimpleMesh(Mesh* mesh, Shader* shader, int deform, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1));

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		double length = 0;
		float add = 0;
		int i = 0;
		float color = 1;
		double z[11] = { 0, 1.25, 2.5, 3.75, 5, 6.25, 7.5, 8.75, 10, 11.25, 12.5 };
		bool colored1[11] = { false };
		bool colored2[11] = { false };
		bool colored3[11] = { false };
		glm::vec3 platform1_colors[11] = { glm::vec3(1, 1, 1) };
		glm::vec3 platform2_colors[11] = { glm::vec3(1, 1, 1) };
		glm::vec3 platform3_colors[11] = { glm::vec3(1, 1, 1) };
		float platform_speed = 1.5;
		//glm::vec3 platform_color = glm::vec3(0, 0, 1);
		float ballX = 0;
		float energyX = 1;
		float ballY = 0.19;
		bool jump = false;
		glm::vec3 ball_color = glm::vec3(1, 0, 0);
		int deform = 0;
		// raza bilei e 0.125
		int generate = 0;
		glm::vec3 colors[6] = { glm::vec3(1, 0, 0), glm::vec3(1, 1, 0), glm::vec3(1, 0.6, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec3(1, 0, 1) };
		bool speed_blocked = false;
		int first_set = 5;
		float time1 = 0;
		float time2 = 0;
		float time3 = 0;
		float time4 = 0;
		float time_no_red = 0;
		float time_red = 0;
		bool modify_energy = true;
		bool key_c = false;
		int start = 1;

	protected:
		Camera* camera;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;
};