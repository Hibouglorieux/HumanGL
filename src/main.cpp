/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 01:52:59 by nathan            #+#    #+#             */
/*   Updated: 2020/08/16 21:47:48 by nathan           ###   ########.fr       */
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

	/*
	RectangularCuboid head(0.6, 0.6, 0.6);
	head.setColor({1.0f, 0.0f, 1.0f});
	RectangularCuboid torso = RectangularCuboid(1, 2, 0.8);
	head.setParent(&torso);
	head.setAnchor({0, 1, 0});
	head.setSelfAnchor({0, -1, 0});
	torso.setColor({1.0f, 0.0f, 0.0f});
	torso.setPos({-1, 0, 0});
	torso.setRot({0, 45, 0});
	torso.setScale({1, 1, 1});
	head.setScale(1, 1, 1);
	RectangularCuboid rightArm(0.2, 1, 0.2);
	rightArm.setColor({0.0f, 0.0f, 1.0f});
	rightArm.setSelfAnchor({1, 1, 0});
	rightArm.setParent(&torso);
	rightArm.setAnchor({-1, 0.9f, 0});
	RectangularCuboid rightForeArm(0.2, 1, 0.2);
	rightForeArm.setColor({0.0f, 0.2f, 0.7f});
	rightForeArm.setSelfAnchor({0, 1, 0});
	rightForeArm.setParent(&rightArm);
	rightForeArm.setAnchor({0, -1, 0});
	*/
	Human human;
	Human human2;
	human2.setPos(3, 0, 0);
	Human human3;
	human3.setPos(0, 3.5, 0);
	human3.setRot(180, 0, 0);
	human3.setScale(0.5, 0.5, 0.5);

	// TODO move to loop
    // draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*
	Matrix test = Matrix::createTranslationMatrix(0, torso.getHeight() / 2 + head.getHeight() / 2, 0) * torso.getModelMat();
	std::cout << "test" << std::endl;
	test.print();
	*/
	human.draw(viewMat);
	human2.draw(viewMat);
	human3.draw(viewMat);
	Loop::loop();

	return 1;
}
