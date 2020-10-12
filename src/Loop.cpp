/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Loop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 15:40:25 by nathan            #+#    #+#             */
/*   Updated: 2020/10/12 14:10:55 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Loop.hpp"
#include <glfw3.h>
#include <unistd.h>
#include "Camera.hpp"
#include "AnimationHandler.hpp"
#include <iomanip>

bool Loop::shouldStop = false;
double Loop::frameTime = 0.0f;
const double Loop::refreshingRate = 1.0 / 60.0;
std::vector<Object*> Loop::objects = {};
World* Loop::world = nullptr;
double Loop::mouseX = 0.0;
double Loop::mouseY = 0.0;
double Loop::fpsRefreshTime = 0.0;
unsigned char Loop::frameCount = 0;

#define SEC_TO_MICROSEC 1000000
#define CAMERA_MOUVEMENT_SPEED 0.3f
#define REFRESH_FPS_RATE 0.5


void Loop::loop()
{
	glfwSetTime(0);
	glfwGetCursorPos(Window::getWindow(), &mouseX, &mouseY);
	glfwSetKeyCallback(Window::getWindow(), Loop::keyCallback);
	while (!glfwWindowShouldClose(Window::getWindow()))
	{
		double currentTimer = glfwGetTime();
		frameCount++;
		processInput();

		//update(frameTime);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		world->render();

		glfwSwapBuffers(Window::getWindow());

		frameTime = glfwGetTime() - currentTimer;
		if (frameTime < refreshingRate)
		{
			usleep((refreshingRate - frameTime) * SEC_TO_MICROSEC);
		}
		if (fpsRefreshTime + 0.5 > currentTimer)
		{
			std::stringstream ss;
			double fps = (float)frameCount / (currentTimer - fpsRefreshTime);
			ss << std::fixed << std::setprecision(1) << fps;
			glfwSetWindowTitle(Window::getWindow(), std::string(std::string("Humangl ") + std::to_string(fps)).c_str());
			frameCount = 0;
			fpsRefreshTime = currentTimer;
		}
	}
}

void Loop::processInput()
{
	glfwPollEvents();
	bool forward, backward, left, right;
	forward = backward = left = right = false;
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(Window::getWindow(), true);
	// camera
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_W) == GLFW_PRESS)
		forward = true;
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_S) == GLFW_PRESS)
		backward = true;
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_D) == GLFW_PRESS)
		right = true;
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_A) == GLFW_PRESS)
		left = true;
	bool shift = glfwGetKey(Window::getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? true : false;
	world->getCamera().move(forward, backward, left, right, (shift == true ? 2 : 1)* CAMERA_MOUVEMENT_SPEED);
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
		world->getCamera().moveUp();
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		world->getCamera().moveDown();

	double oldMouseX = mouseX;
	double oldMouseY = mouseY;
	glfwGetCursorPos(Window::getWindow(), &mouseX, &mouseY);
	world->getCamera().rotate(mouseX - oldMouseX, mouseY - oldMouseY);
}

void Loop::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;// might use for speed of camera
	if (window != Window::getWindow())
		return;
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		world->playNextAnim();
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		world->playPrevAnim();
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		world->cancelAnimation();
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		world->addHuman();
	if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS)
		world->clearObject("tmpHuman");
}
