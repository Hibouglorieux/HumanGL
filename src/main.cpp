/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 01:52:59 by nathan            #+#    #+#             */
/*   Updated: 2020/10/12 11:56:36 by nathan           ###   ########.fr       */
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
	// need to set gl parameters
    glEnable(GL_DEPTH_TEST);

    Matrix viewMat = Matrix::createTranslationMatrix(0, -2.0f, -10);

	/*
	Human human;
	Human* human2 = new Human();
	human2->setPos(3, 0, 0);
	Human human3;
	human3.setPos(0, 3.5, 0);
	human3.setRot(180, 0, 0);
	human3.setScale(0.5);
	*/


	/*
	RectangularCuboid base(3, 3, 3);
	RectangularCuboid mid(0.5, 2, 0.5);
	RectangularCuboid arm(0.5, 2, 0.5);
	base.setPos(0, 0, 0);
	base.setColor({1.0, 0, 0});
	base.setSelfAnchor({0, -0.5, 0});

	mid.setColor({1, 1, 1});
	mid.debug = true;
	mid.setParent(&base);
	mid.setPos({1, 1, 0});
	mid.setSelfAnchor({-1, 1, 0});
	mid.setRot(0, 0, 0);
	mid.setRot(0, 0, 90);

	arm.setRot(0, 0, 0);
	arm.setParent(&mid);
	arm.setPos(0, -1, 0);
	arm.setSelfAnchor({0, 1, 0});
	arm.setColor({1.0, 0, 0});


	*/

	Camera camera;
	World* world = new World();
	Human* human = new Human();
	RectangularCuboid* floor = new RectangularCuboid(1000, 0.1, 1000);
	floor->setColor({0.6, 0.7, 0.6});
	human->setPos(0, 4.9f, 0);
	floor->setShader(new Shader("floor.vert", "floor.frag"));

	world->setCamera(camera);
	world->addObject(human);
	world->addObject(floor);
	Loop::setWorld(world);

//	bvhParser::loadFile("blend-export.bvh").test();
	//human->setScale(8);
	//human2->setScale(8);

	//base.draw(viewMat);
	//mid.draw(viewMat);
	//arm.draw(viewMat);
//	center.draw(viewMat);
//	pouet.draw(viewMat);
	/*
	human.draw(viewMat);
	human2->draw(viewMat);
	delete human2;
	human3.draw(viewMat);
	*/
	Loop::loop();

	return 1;
}
