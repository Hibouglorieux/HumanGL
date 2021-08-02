/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 01:52:59 by nathan            #+#    #+#             */
/*   Updated: 2021/08/02 15:39:22 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GL/glew.h>
#include "Utilities.h"
#include "Window.hpp"
#include "Human.hpp"
#include "Loop.hpp"
#include "World.hpp"
#include "Matrix.hpp"
#include "bvhParser.hpp"

using namespace std;

int		main( void )
{
	if (!Window::init())
		return (0);

	if (glewInit() != GLEW_OK)
	{
		std::cerr <<  "Failed to initialize GLEW\n" << std::endl;
		return 0;
	}

	glStencilMask(0xFF);

	Camera camera;
	World* world = new World();
	Human* human = new Human();
	RectangularCuboid* floor = new RectangularCuboid(1000, 0.1, 1000);
	floor->setID("floor");
	floor->setColor({0.6, 0.7, 0.6});
	human->setPos(0, 4.9f, 0);
	floor->setShader(new Shader("floor.vert", "floor.frag"));

	world->setCamera(camera);
	world->addObject(human);
	world->addObject(floor);
	Loop::setWorld(world);

	Loop::loop();
	delete world;

	return 1;
}
