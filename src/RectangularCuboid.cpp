/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RectangularCuboid.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:52:01 by nathan            #+#    #+#             */
/*   Updated: 2020/08/26 11:22:16 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RectangularCuboid.hpp"

RectangularCuboid::RectangularCuboid(float width, float height, float depth)
	: shader("shaders/plaincolor.vert", "shaders/plaincolor.frag"), color({0.0f, 0.7f, 0.7f})
{
	scale = Vec3(width, height, depth);
	rot = Vec3(0, 0, 0);
	pos = Vec3(0, 0, 0);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
  
	debug = false;
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

Matrix RectangularCuboid::getParentMatrix()
{
	if (parent == nullptr)
	{
		std::cerr << "getParent called with no parent" << std::endl;
		return Matrix();
	}
	if (dynamic_cast<RectangularCuboid*>(parent)->shouldUpdateMats)
		dynamic_cast<RectangularCuboid*>(parent)->updateMatrixes();
	return dynamic_cast<RectangularCuboid*>(parent)->myMat;
}

void RectangularCuboid::updateMatrixes()
{
	Matrix parentMat;
	Vec3 parentScale;
	if (parent != nullptr)
	{
		parentMat = getParentMatrix();
		parentScale = dynamic_cast<RectangularCuboid*>(parent)->scale;
	}
	else
	{
		parentMat = Matrix();
		parentScale = {1.0, 1.0, 1.0};
	}
	if (debug)
	{
		std::cout << "parentMat" << std::endl;
		parentMat.print();
	}
	myMat = parentMat * Matrix::createTranslationMatrix(pos * parentScale * 0.5);
	if (debug)
	{
		std::cout << "myMat before rot" << std::endl;
		myMat.print();
	}
	rotMat = Matrix();
	if (rot.y != 0)
		rotMat *= Matrix::createRotationMatrix(Matrix::RotationDirection::Y, rot.y);
	if (rot.x != 0)
		rotMat *= Matrix::createRotationMatrix(Matrix::RotationDirection::X, rot.x);
	if (rot.z != 0)
		rotMat *= Matrix::createRotationMatrix(Matrix::RotationDirection::Z, rot.z);
	myMat *= rotMat;// need this
	if (debug)
	{
		std::cout << "myMat after rot" << std::endl;
		myMat.print();
	}
	Matrix mySelfAnchor = Matrix::createTranslationMatrix(selfAnchor * scale * -0.5);
	myMat *= mySelfAnchor;
	if (debug)
	{
		std::cout << "myselfanchor" << std::endl;
		Matrix::createTranslationMatrix(selfAnchor * scale * 0.5).print();
		std::cout << "myMat final after self anchor" << std::endl;
		myMat.print();
	}
	scaleMat = Matrix::createScaleMatrix(scale);
	modelMat = myMat * scaleMat;
	if (debug)
	{
		std::cout << "modelMal" << std::endl;
		modelMat.print();
	}

	shouldUpdateMats = false;
}

/*
void RectangularCuboid::updateMatrixes()
{
	RectangularCuboid* tmpParent = dynamic_cast<RectangularCuboid*>(parent);
	RectangularCuboid* tmpChild = this;
	if (debug)
	{
		std::cout << "parentMat ";
		tmpParent->getModelMat().print();
	}
	Vec3 tmpPos, tmpRot;
	while (tmpParent)
	{
		if (tmpChild->hasAnchor)
		{
			Vec3 anchoredPos = tmpParent->getRelativePos(tmpChild->anchor);
			//anchoredPos = tmpParent->getModelMat().vectorMult(anchoredPos);
			if (debug)
			{
			std::cout << "anchored Pos ";
			anchoredPos.print();
			}
			//anchoredPos = tmpParent->rotMat.vectorMult(anchoredPos);
			tmpPos += anchoredPos;
		}
		tmpPos += tmpParent->getPos();
		tmpRot += tmpParent->getRot();
		tmpChild = tmpParent;
		tmpParent = dynamic_cast<RectangularCuboid*>(tmpParent->getParent());
	}
	tmpPos += pos;
	tmpRot += rot;

	rotMat = Matrix();
	if (tmpRot.y != 0)
		rotMat *= Matrix::createRotationMatrix(Matrix::RotationDirection::Y, tmpRot.y);
	if (tmpRot.x != 0)
		rotMat *= Matrix::createRotationMatrix(Matrix::RotationDirection::X, tmpRot.x);
	if (tmpRot.z != 0)
		rotMat *= Matrix::createRotationMatrix(Matrix::RotationDirection::Z, tmpRot.z);

	Vec3 test = rotMat.vectorMult(-selfAnchor * 0.5 * scale);
	if (debug)
	{
	std::cout << "test ";
	test.print();
	}
	//tmpPos += rotMat.vectorMult(-selfAnchor * 0.5 * scale);

	if (debug)
	{
		std::cout << "tmpPos";
		tmpPos.print();
	}
	transMat = Matrix::createTranslationMatrix(tmpPos);
	//transMat = Matrix::createTranslationMatrix(tmpPos - selfAnchor * scale * 0.5 + (selfAnchor * 0.5 * scale));
	if (debug)
	{
		std::cout << "transMat ";
		transMat.print();
	}

	scaleMat = Matrix::createScaleMatrix(scale);

	//modelMat = transMat * rotMat * scaleMat;
	if (parent && dynamic_cast<RectangularCuboid*>(parent)->shouldUpdateMats)
	{
		dynamic_cast<RectangularCuboid*>(parent)->updateMatrixes();	
		modelMat = dynamic_cast<RectangularCuboid*>(parent)->getModelMat();
	}
	else
		modelMat = Matrix();
	modelMat = modelMat * transMat * rotMat * Matrix::createTranslationMatrix(-selfAnchor * 0.5 * scale) * scaleMat;
	if (debug)
	{
		std::cout << "modelMat ";
		modelMat.print();
	}

	shouldUpdateMats = false;
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
			if (tmpParent->shouldUpdateMats)
				tmpParent->updateMatrixes();
			Vec3 anchoredPos = {tmpChild->anchor.x * tmpParent->getScale().x * 0.5f,
								tmpChild->anchor.y * tmpParent->getScale().y * 0.5f,
								tmpChild->anchor.z * tmpParent->getScale().z * 0.5f};
			anchoredPos.x -= tmpChild->selfAnchor.x * tmpChild->getScale().x * 0.5f;
			anchoredPos.y -= tmpChild->selfAnchor.y * tmpChild->getScale().y * 0.5f;
			anchoredPos.z -= tmpChild->selfAnchor.z * tmpChild->getScale().z * 0.5f;
			anchoredPos.print();
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
*/
