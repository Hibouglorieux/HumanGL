/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RectangularCuboid.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:52:01 by nathan            #+#    #+#             */
/*   Updated: 2020/08/16 05:33:27 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RectangularCuboid.hpp"

RectangularCuboid::RectangularCuboid(float width, float height, float depth)
	: shader("shaders/plaincolor.vert", "shaders/plaincolor.frag"), color({0.0f, 0.7f, 0.7f})
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
  
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

	_width = width;
	_height = height;
	_depth = depth;
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
	shouldUpdateMats = true;
}

RectangularCuboid::RectangularCuboid( void ) : RectangularCuboid(1, 1, 1){}

RectangularCuboid::~RectangularCuboid( void ) 
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glInvalidateBufferData(VBO);
}

void RectangularCuboid::setMat(Matrix newMat, int type)
{
	if (type == TRANS_MAT)
		transMat = newMat;
	if (type == ROT_MAT)
		rotMat = newMat;
	if (type == SCALE_MAT)
		scaleMat = newMat;
	shouldUpdateMats = true;
}

void RectangularCuboid::setColor(std::array<float, 3> newColor)
{
	color = newColor;
}

void RectangularCuboid::draw(Matrix viewMat)
{
	if (shouldUpdateMats)
		updateMatrixes();
	Matrix precalcMat = projMat * viewMat * modelMat;
	modelMat.print();
    glUseProgram(shader.ID);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "proj"), 1, GL_TRUE, projMat.exportForGL());
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_TRUE, viewMat.exportForGL());
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_TRUE, modelMat.exportForGL());
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "precalcMat"), 1, GL_TRUE, precalcMat.exportForGL());
    glUniform3fv(glGetUniformLocation(shader.ID, "myColor"), 1, &color.front());
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

Matrix RectangularCuboid::getModelMat()
{
	return modelMat;
}

void RectangularCuboid::onNewParent()
{
	shouldUpdateMats = true;
}

void RectangularCuboid::updateMatrixes()
{
	RectangularCuboid* tmpParent = dynamic_cast<RectangularCuboid*>(parent);
	Matrix tmpTransMat, tmpRotMat, tmpScaleMat;
	while (tmpParent)
	{
		tmpTransMat *= tmpParent->transMat;
		tmpRotMat *= tmpParent->rotMat;
		tmpScaleMat *= tmpParent->scaleMat;
		tmpParent = dynamic_cast<RectangularCuboid*>(tmpParent->getParent());
	}
	tmpTransMat *= transMat;
	tmpRotMat *= rotMat;
	tmpScaleMat *= scaleMat;
	//modelMat = tmpTransMat * tmpRotMat * tmpScaleMat;
	modelMat = tmpScaleMat * tmpTransMat * tmpRotMat; // fix for scale position ?
	shouldUpdateMats = false;
}
