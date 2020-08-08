/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 01:52:59 by nathan            #+#    #+#             */
/*   Updated: 2020/08/08 22:14:20 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GL/glew.h>
#include "Utilities.h"
#include "Window.hpp"
#include "Cube.hpp"
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

    Cube cube = Cube(1, Matrix::createTranslationMatrix(0, 2.7f, 0));
	RectangularCuboid torso = RectangularCuboid(2, 4, 3);
	torso.setColor({1.0f, 0.0f, 0.0f});

    // draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cube.draw(viewMat);
	torso.draw(viewMat);
	Loop::loop();

	return 1;
}
