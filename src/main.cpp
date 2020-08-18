/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 01:52:59 by nathan            #+#    #+#             */
/*   Updated: 2020/08/18 06:04:18 by nathan           ###   ########.fr       */
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

    Matrix viewMat = Matrix::createTranslationMatrix(0, -2.0f, -10);

	Human human;
	Human* human2 = new Human();
	human2->setPos(3, 0, 0);
	Human human3;
	human3.setPos(0, 3.5, 0);
	human3.setRot(180, 0, 0);
	human3.setScale(0.5);
	std::cout << human.body[Human::rightArm]->getPos().toString() << std::endl;
	RectangularCuboid test(0.5, 2, 0.5);


	// TODO move to loop
    // draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*
	Matrix test = Matrix::createTranslationMatrix(0, torso.getHeight() / 2 + head.getHeight() / 2, 0) * torso.getModelMat();
	std::cout << "test" << std::endl;
	test.print();
	*/
	human.draw(viewMat);
	human2->draw(viewMat);
	delete human2;
	human3.draw(viewMat);
	Loop::loop();

	return 1;
}
