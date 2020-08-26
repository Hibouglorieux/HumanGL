/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 01:52:59 by nathan            #+#    #+#             */
/*   Updated: 2020/08/26 11:24:09 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GL/glew.h>
#include "Utilities.h"
#include "Window.hpp"
#include "Human.hpp"
#include "Loop.hpp"
#include "Matrix.hpp"

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

    Matrix viewMat = Matrix::createTranslationMatrix(0, -2.0f, -20);

	/*
	Human human;
	Human* human2 = new Human();
	human2->setPos(3, 0, 0);
	Human human3;
	human3.setPos(0, 3.5, 0);
	human3.setRot(180, 0, 0);
	human3.setScale(0.5);
	*/


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


	// TODO move to loop
    // draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Human human;
	human.draw(viewMat);
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
