/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Human.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 21:11:31 by nathan            #+#    #+#             */
/*   Updated: 2021/08/02 15:21:33 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Human.hpp"

const int Human::nbOfLimbs = 10;

Human::Human()
{
	body.resize(rightLeg + 1);

	body[chest] = new RectangularCuboid(0.7, 2, 0.4);
	body[chest]->setColor({1.0f, 0.0f, 0.0f});
	body[chest]->setSelfAnchor({0, -1, 0});

	body[head] = new RectangularCuboid(0.7, 0.7, 0.7);
	body[head]->setColor({1.0f, 0.0f, 1.0f});
	body[head]->setParent(body[chest]);
	body[head]->setPos({0, 1, 0});
	body[head]->setSelfAnchor({0, -1, 0});

	body[rightArm] = new RectangularCuboid(1.0, 0.2, 0.2);
	body[rightArm]->setColor({0.0f, 0.0f, 1.0f});
	body[rightArm]->setSelfAnchor({1, 0, 0});
	body[rightArm]->setParent(body[chest]);
	body[rightArm]->setPos({-1, 0.8f, 0});

	body[rightForeArm] = new RectangularCuboid(1.0, 0.2, 0.2);
	body[rightForeArm]->setColor({0.0f, 0.2f, 0.7f});
	body[rightForeArm]->setSelfAnchor({1, 0, 0});
	body[rightForeArm]->setParent(body[rightArm]);
	body[rightForeArm]->setPos({-1, 0, 0});

	body[leftArm] = new RectangularCuboid(1.0, 0.2, 0.2);
	body[leftArm]->setColor({0.0f, 0.0f, 1.0f});
	body[leftArm]->setSelfAnchor({-1, 0, 0});
	body[leftArm]->setParent(body[chest]);
	body[leftArm]->setPos({1, 0.8f, 0});

	body[leftForeArm] = new RectangularCuboid(1.0, 0.2, 0.2);
	body[leftForeArm]->setColor({0.0f, 0.2f, 0.7f});
	body[leftForeArm]->setSelfAnchor({-1, 0, 0});
	body[leftForeArm]->setParent(body[leftArm]);
	body[leftForeArm]->setPos({1, 0, 0});

	body[leftUpLeg] = new RectangularCuboid(0.3, 1.2, 0.4);
	body[leftUpLeg]->setColor({0.0f, 0.0f, 0.4f});
	body[leftUpLeg]->setParent(body[chest]);
	body[leftUpLeg]->setSelfAnchor({0, 1, 0});
	body[leftUpLeg]->setPos({0.4, -1, 0});

	body[leftLeg] = new RectangularCuboid(0.3, 1.2, 0.4);
	body[leftLeg]->setColor({0.4f, 0.0f, 0.4f});
	body[leftLeg]->setParent(body[leftUpLeg]);
	body[leftLeg]->setSelfAnchor({0, 1, 0});
	body[leftLeg]->setPos({0, -1, 0});

	body[rightUpLeg] = new RectangularCuboid(0.3, 1.2, 0.4);
	body[rightUpLeg]->setColor({0.0f, 0.0f, 0.4f});
	body[rightUpLeg]->setParent(body[chest]);
	body[rightUpLeg]->setSelfAnchor({0, 1, 0});
	body[rightUpLeg]->setPos({-0.4, -1, 0});

	body[rightLeg] = new RectangularCuboid(0.3, 1.2, 0.4);
	body[rightLeg]->setColor({0.4f, 0.0f, 0.4f});
	body[rightLeg]->setParent(body[rightUpLeg]);
	body[rightLeg]->setSelfAnchor({0, 1, 0});
	body[rightLeg]->setPos({0, -1, 0});
}

Human::~Human()
{
	for (RectangularCuboid* part : body)
	{
		delete part;
	}
	body.clear();
}

void Human::setScale(float x)
{
	Vec3 scalexyz = {x, x, x};
	body[head]->setScale(body[head]->getScale() * x);
	body[chest]->setScale(body[chest]->getScale() * x);
	body[rightArm]->setScale(body[rightArm]->getScale() * x);
	body[leftArm]->setScale(body[leftArm]->getScale() * x);
	body[rightForeArm]->setScale(body[rightForeArm]->getScale() * x);
	body[leftForeArm]->setScale(body[leftForeArm]->getScale() * x);
	body[leftUpLeg]->setScale(body[leftUpLeg]->getScale() * x);
	body[rightUpLeg]->setScale(body[rightUpLeg]->getScale() * x);
	body[leftLeg]->setScale(body[leftLeg]->getScale() * x);
	body[rightLeg]->setScale(body[rightLeg]->getScale() * x);
}

void Human::draw(Matrix* viewMat)
{
	update();
	body[chest]->draw(viewMat);
	body[chest]->drawChildren(viewMat);
}

void Human::draw(Matrix* viewMat, Shader* specialEffect, std::vector<std::tuple<std::function<void(GLint, GLsizei, const GLfloat*)>, std::string, const GLfloat*>> shaderData)
{
	body[chest]->draw(viewMat, specialEffect, shaderData);
	body[chest]->drawChildren(viewMat, specialEffect, shaderData);
}

void Human::update()
{
	if (animation.numberOfFrames > 0)
	{
		for (int limb = 1; limb < nbOfLimbs; limb++)
		{
			body[limb]->setRot(animation.data[frameCount][limb]);
		}
		body[chest]->setPos(animation.translationData[frameCount] + pos);
		body[chest]->setRot(animation.data[frameCount][chest]);
		frameCount++;
		if (frameCount == animation.numberOfFrames)
			frameCount = 0;
	}
}

void Human::setPos(float x, float y, float z)
{
	pos = Vec3(x, y, z);
	body[chest]->setPos(pos);
}

Vec3 Human::getPos() const
{
	return this->pos;
}

void Human::setRot(float x, float y, float z)
{
	body[chest]->setInitialRot(Vec3(x, y, z));
}

void Human::playAnimation(bvhData newAnim)
{
	animation = newAnim;
	frameCount = 0;
}

void Human::cancelAnimation()
{
	animation.numberOfFrames = 0;
	animation.data.clear();
	frameCount = 0;
	for (int limb = 0; limb < nbOfLimbs; limb++)
	{
		body[limb]->setRot(Vec3::ZERO);
	}
	body[chest]->setPos(pos);
}

RectangularCuboid* Human::getBodyPart(Body bodyPart)
{
	return body[bodyPart];
}
