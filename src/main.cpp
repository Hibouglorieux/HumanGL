/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 01:52:59 by nathan            #+#    #+#             */
/*   Updated: 2020/08/16 05:33:48 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GL/glew.h>
#include "Utilities.h"
#include "Window.hpp"
#include "RectangularCuboid.hpp"
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

	RectangularCuboid head(1, 1, 1);
	head.setColor({1.0f, 0.0f, 1.0f});
	RectangularCuboid torso = RectangularCuboid(2, 4, 3);
	head.setMat(Matrix::createTranslationMatrix(0, torso.getHeight() / 2 + head.getHeight() / 2, 0), TRANS_MAT);
	head.setParent(&torso);
	torso.setColor({1.0f, 0.0f, 0.0f});
	torso.setMat(Matrix::createTranslationMatrix(-1, 0, 0), TRANS_MAT);
	torso.setMat(Matrix::createRotationMatrix(Matrix::RotationDirection::Y, 45), ROT_MAT);
	torso.setMat(Matrix::createScaleMatrix(2, 2, 2), SCALE_MAT);

	// TODO move to loop
    // draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	torso.draw(viewMat);
    head.draw(viewMat);
	Loop::loop();

	return 1;
}
