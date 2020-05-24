/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 01:52:59 by nathan            #+#    #+#             */
/*   Updated: 2020/05/24 03:12:16 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GL/glew.h>
#include "Utilities.h"
#include "Window.hpp"
#include "Cube.hpp"
using namespace std;

int		main( void )
{
    Window w;
	if (!w.init())
		return (0);

	if (glewInit() != GLEW_OK)
	{
		std::cerr <<  "Failed to initialize GLEW\n" << std::endl;
		return 0;
	}
	// need to set gl parameters
    glEnable(GL_DEPTH_TEST);

    float modelMat[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0 ,0,0,0,1};
    float viewMat[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0 ,0,0,-10,1};
    Cube cube{{0, 1, 0}};
    cube.setModelMat(modelMat);

    // draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cube.draw(viewMat);
    glfwSwapBuffers(w.window);
    getchar();

	return 1;
}
