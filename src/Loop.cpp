/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Loop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 15:40:25 by nathan            #+#    #+#             */
/*   Updated: 2020/09/02 01:30:06 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Loop.hpp"
#include <glfw3.h>
#include <unistd.h>
#include "Window.hpp"

bool Loop::shouldStop = false;
double Loop::frameTime = 0.0f;
const double Loop::refreshingRate = 1.0 / 60.0;
std::vector<Object*> Loop::objects = {};
World* Loop::world = nullptr;

#define SEC_TO_MICROSEC 1000000


void Loop::loop()
{
	glfwSetTime(0);
	while (!glfwWindowShouldClose(Window::getWindow()))
	{
		double currentTimer = glfwGetTime();
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
	}
}

void Loop::processInput()
{
	glfwPollEvents();
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(Window::getWindow(), true);
}
