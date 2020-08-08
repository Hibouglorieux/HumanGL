/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RectangularCuboid.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:52:01 by nathan            #+#    #+#             */
/*   Updated: 2020/08/08 21:16:54 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RectangularCuboid.hpp"

RectangularCuboid::RectangularCuboid(float width, float height, float depth, Matrix modelMatrix)
	: modelMat(modelMatrix), shader("shaders/plaincolor.vert", "shaders/plaincolor.frag"), color({0.0f, 0.7f, 0.7f})
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
  
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

	width /= 2;
	height /= 2;
	depth /= 2;
    float vertices[] = {
        -width, -height, -depth,  0.0f, 0.0f,
        width, -height, -depth,  1.0f, 0.0f,
        width,  height, -depth,  1.0f, 1.0f,
        width,  height, -depth,  1.0f, 1.0f,
        -width,  height, -depth,  0.0f, 1.0f,
        -width, -height, -depth,  0.0f, 0.0f,

        -width, -height,  depth,  0.0f, 0.0f,
        width, -height,  depth,  1.0f, 0.0f,
        width,  height,  depth,  1.0f, 1.0f,
        width,  height,  depth,  1.0f, 1.0f,
        -width,  height,  depth,  0.0f, 1.0f,
        -width, -height,  depth,  0.0f, 0.0f,

        -width,  height,  depth,  1.0f, 0.0f,
        -width,  height, -depth,  1.0f, 1.0f,
        -width, -height, -depth,  0.0f, 1.0f,
        -width, -height, -depth,  0.0f, 1.0f,
        -width, -height,  depth,  0.0f, 0.0f,
        -width,  height,  depth,  1.0f, 0.0f,

        width,  height,  depth,  1.0f, 0.0f,
        width,  height, -depth,  1.0f, 1.0f,
        width, -height, -depth,  0.0f, 1.0f,
        width, -height, -depth,  0.0f, 1.0f,
        width, -height,  depth,  0.0f, 0.0f,
        width,  height,  depth,  1.0f, 0.0f,

        -width, -height, -depth,  0.0f, 1.0f,
        width, -height, -depth,  1.0f, 1.0f,
        width, -height,  depth,  1.0f, 0.0f,
        width, -height,  depth,  1.0f, 0.0f,
        -width, -height,  depth,  0.0f, 0.0f,
        -width, -height, -depth,  0.0f, 1.0f,

        -width,  height, -depth,  0.0f, 1.0f,
        width,  height, -depth,  1.0f, 1.0f,
        width,  height,  depth,  1.0f, 0.0f,
        width,  height,  depth,  1.0f, 0.0f,
        -width,  height,  depth,  0.0f, 0.0f,
        -width,  height, -depth,  0.0f, 1.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  

    // vertex positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    glBindVertexArray(0);
}

RectangularCuboid::RectangularCuboid( void ) : RectangularCuboid(1, 1, 1){}

RectangularCuboid::~RectangularCuboid( void ) 
{
	//TODO clear VAO
}

void RectangularCuboid::setModelMat(Matrix newModelMat)
{
	modelMat = newModelMat;
}

void RectangularCuboid::setColor(std::array<float, 3> newColor)
{
	color = newColor;
}

void RectangularCuboid::draw(Matrix viewMat)
{
	Matrix precalcMat = projMat * viewMat * modelMat;
    glUseProgram(shader.ID);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "proj"), 1, GL_TRUE, projMat.exportForGL());
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_TRUE, viewMat.exportForGL());
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_TRUE, modelMat.exportForGL());
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "precalcMat"), 1, GL_TRUE, precalcMat.exportForGL());
    glUniform3fv(glGetUniformLocation(shader.ID, "myColor"), 1, &color.front());
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
