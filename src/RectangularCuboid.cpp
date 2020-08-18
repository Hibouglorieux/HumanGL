/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RectangularCuboid.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:52:01 by nathan            #+#    #+#             */
/*   Updated: 2020/08/18 05:58:05 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RectangularCuboid.hpp"

RectangularCuboid::RectangularCuboid(float width, float height, float depth)
	: shader("shaders/plaincolor.vert", "shaders/plaincolor.frag"), color({0.0f, 0.7f, 0.7f})
{
	hasAnchor = false;
	scale = Vec3(width, height, depth);
	rot = Vec3(0, 0, 0);
	pos = Vec3(0, 0, 0);
	anchor = Vec3(0, 0, 0);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
  
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    float vertices[] = {
        -0.5, -0.5, -0.5,  0.0f, 0.0f,
        0.5, -0.5, -0.5,  1.0f, 0.0f,
        0.5,  0.5, -0.5,  1.0f, 1.0f,
        0.5,  0.5, -0.5,  1.0f, 1.0f,
        -0.5,  0.5, -0.5,  0.0f, 1.0f,
        -0.5, -0.5, -0.5,  0.0f, 0.0f,

        -0.5, -0.5,  0.5,  0.0f, 0.0f,
        0.5, -0.5,  0.5,  1.0f, 0.0f,
        0.5,  0.5,  0.5,  1.0f, 1.0f,
        0.5,  0.5,  0.5,  1.0f, 1.0f,
        -0.5,  0.5,  0.5,  0.0f, 1.0f,
        -0.5, -0.5,  0.5,  0.0f, 0.0f,

        -0.5,  0.5,  0.5,  1.0f, 0.0f,
        -0.5,  0.5, -0.5,  1.0f, 1.0f,
        -0.5, -0.5, -0.5,  0.0f, 1.0f,
        -0.5, -0.5, -0.5,  0.0f, 1.0f,
        -0.5, -0.5,  0.5,  0.0f, 0.0f,
        -0.5,  0.5,  0.5,  1.0f, 0.0f,

        0.5,  0.5,  0.5,  1.0f, 0.0f,
        0.5,  0.5, -0.5,  1.0f, 1.0f,
        0.5, -0.5, -0.5,  0.0f, 1.0f,
        0.5, -0.5, -0.5,  0.0f, 1.0f,
        0.5, -0.5,  0.5,  0.0f, 0.0f,
        0.5,  0.5,  0.5,  1.0f, 0.0f,

        -0.5, -0.5, -0.5,  0.0f, 1.0f,
        0.5, -0.5, -0.5,  1.0f, 1.0f,
        0.5, -0.5,  0.5,  1.0f, 0.0f,
        0.5, -0.5,  0.5,  1.0f, 0.0f,
        -0.5, -0.5,  0.5,  0.0f, 0.0f,
        -0.5, -0.5, -0.5,  0.0f, 1.0f,

        -0.5,  0.5, -0.5,  0.0f, 1.0f,
        0.5,  0.5, -0.5,  1.0f, 1.0f,
        0.5,  0.5,  0.5,  1.0f, 0.0f,
        0.5,  0.5,  0.5,  1.0f, 0.0f,
        -0.5,  0.5,  0.5,  0.0f, 0.0f,
        -0.5,  0.5, -0.5,  0.0f, 1.0f
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
	//Matrix precalcMat = projMat * viewMat * modelMat;
	Matrix precalcMat = projMat * viewMat;
	precalcMat *= modelMat;
    glUseProgram(shader.ID);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "proj"), 1, GL_TRUE, projMat.exportForGL());
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_TRUE, viewMat.exportForGL());
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_TRUE, modelMat.exportForGL());
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "precalcMat"), 1, GL_TRUE, precalcMat.exportForGL());
    glUniform3fv(glGetUniformLocation(shader.ID, "myColor"), 1, &color.front());
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void RectangularCuboid::drawChildren(Matrix viewMat)
{
	for (auto child : this->getChildren())
	{
		child->draw(viewMat);
		child->drawChildren(viewMat);
	}
}

Matrix RectangularCuboid::getModelMat()
{
	return modelMat;
}

void RectangularCuboid::onNewParent()
{
	shouldUpdateMats = true;		
}

void RectangularCuboid::setPos(Vec3 newPos)
{
	pos = newPos;
	shouldUpdateMats = true;
}

void RectangularCuboid::setRot(Vec3 newRot)
{
	rot = newRot;
	shouldUpdateMats = true;
}

void RectangularCuboid::setScale(Vec3 newScale)
{
	scale = newScale;
	shouldUpdateMats = true;
}

void RectangularCuboid::setAnchor(Vec3 newAnchor)
{
	hasAnchor = true;
	anchor = newAnchor;
}

void RectangularCuboid::updateMatrixes()
{
	RectangularCuboid* tmpParent = dynamic_cast<RectangularCuboid*>(parent);
	RectangularCuboid* tmpChild = this;
	Vec3 tmpPos, tmpRot;
	while (tmpParent)
	{
		if (tmpChild->hasAnchor)
		{
			Vec3 anchoredPos = {tmpChild->anchor.x * tmpParent->getScale().x * 0.5f,
								tmpChild->anchor.y * tmpParent->getScale().y * 0.5f,
								tmpChild->anchor.z * tmpParent->getScale().z * 0.5f};
			anchoredPos.x -= tmpChild->selfAnchor.x * tmpChild->getScale().x * 0.5f;
			anchoredPos.y -= tmpChild->selfAnchor.y * tmpChild->getScale().y * 0.5f;
			anchoredPos.z -= tmpChild->selfAnchor.z * tmpChild->getScale().z * 0.5f;
			if (tmpParent->shouldUpdateMats)
				tmpParent->updateMatrixes();
			anchoredPos = tmpParent->rotMat.vectorMult(anchoredPos);
			tmpPos += anchoredPos;
		}
		tmpPos += tmpParent->getPos();
		tmpRot += tmpParent->getRot();
		tmpChild = tmpParent;
		tmpParent = dynamic_cast<RectangularCuboid*>(tmpParent->getParent());
	}
	tmpPos += pos;
	tmpRot += rot;

	transMat = Matrix::createTranslationMatrix(tmpPos + (selfAnchor * scale * 0.5));
	rotMat = Matrix();
	if (tmpRot.y != 0)
		rotMat *= Matrix::createRotationMatrix(Matrix::RotationDirection::Y, tmpRot.y);
	if (tmpRot.x != 0)
		rotMat *= Matrix::createRotationMatrix(Matrix::RotationDirection::X, tmpRot.x);
	if (tmpRot.z != 0)
		rotMat *= Matrix::createRotationMatrix(Matrix::RotationDirection::Z, tmpRot.z);
	scaleMat = Matrix::createScaleMatrix(scale);
	//modelMat = transMat * rotMat * scaleMat;
	modelMat = transMat * rotMat * Matrix::createTranslationMatrix(-selfAnchor * scale * 0.5) * scaleMat;
	shouldUpdateMats = false;
}
/*
void RectangularCuboid::updateMatrixes()
{
	RectangularCuboid* tmpParent = dynamic_cast<RectangularCuboid*>(parent);
	Matrix tmpTransMat, tmpRotMat, tmpScaleMat;
	while (tmpParent)
	{
		_posX += tmpParent->posX() * tmpParent->scaleX();
		_posY += tmpParent->posY() * tmpParent->scaleY();
		_posZ += tmpParent->posZ() * tmpParent->scaleZ();
		_rotX += tmpParent->rotX();
		_rotY += tmpParent->rotY();
		_rotZ += tmpParent->rotZ();
		tmpTransMat *= tmpParent->transMat;
		tmpRotMat *= tmpParent->rotMat;
		tmpScaleMat *= tmpParent->scaleMat;// Fix idea : instead of getting scale mat, mult transmat by another transmat from x y z component of scale mat,
		tmpParent = dynamic_cast<RectangularCuboid*>(tmpParent->getParent());
	}
	tmpTransMat *= transMat;
	tmpRotMat *= rotMat;
	tmpScaleMat *= scaleMat;
	//modelMat = tmpTransMat * tmpRotMat * tmpScaleMat;
	modelMat = tmpScaleMat * tmpTransMat * tmpRotMat; // fix for scale position ?
	shouldUpdateMats = false;
}
*/
