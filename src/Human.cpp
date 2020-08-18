/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Human.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 21:11:31 by nathan            #+#    #+#             */
/*   Updated: 2020/08/18 06:03:29 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Human.hpp"

Human::Human()
{
	body.resize(rightLeg + 1);

	body[torso] = new RectangularCuboid(1, 2, 0.8);
	body[torso]->setColor({1.0f, 0.0f, 0.0f});

	body[head] = new RectangularCuboid(0.6, 0.6, 0.6);
	body[head]->setColor({1.0f, 0.0f, 1.0f});
	body[head]->setParent(body[torso]);
	body[head]->setAnchor({0, 1, 0});
	body[head]->setSelfAnchor({0, -1, 0});


	body[rightArm] = new RectangularCuboid(0.2, 1, 0.2);
	body[rightArm]->setColor({0.0f, 0.0f, 1.0f});
	body[rightArm]->setRot({0, 0, -90});
	body[rightArm]->setSelfAnchor({1, 1, 0});
	body[rightArm]->setParent(body[torso]);
	body[rightArm]->setAnchor({-1, 0.8f, 0});

	body[rightForeArm] = new RectangularCuboid(0.2, 1, 0.2);
	body[rightForeArm]->setColor({0.0f, 0.2f, 0.7f});
	body[rightForeArm]->setSelfAnchor({0, 1, 0});
	body[rightForeArm]->setParent(body[rightArm]);
	body[rightForeArm]->setAnchor({0, -1, 0});

	body[leftArm] = new RectangularCuboid(0.2, 1, 0.2);
	body[leftArm]->setColor({0.0f, 0.0f, 1.0f});
	body[leftArm]->setSelfAnchor({-1, 1, 0});
	body[leftArm]->setParent(body[torso]);
	body[leftArm]->setAnchor({1, 0.8f, 0});

	body[leftForeArm] = new RectangularCuboid(0.2, 1, 0.2);
	body[leftForeArm]->setColor({0.0f, 0.2f, 0.7f});
	body[leftForeArm]->setSelfAnchor({0, 1, 0});
	body[leftForeArm]->setParent(body[leftArm]);
	body[leftForeArm]->setAnchor({0, -1, 0});

	body[leftUpLeg] = new RectangularCuboid(0.3, 1.2, 0.4);
	body[leftUpLeg]->setColor({0.0f, 0.0f, 0.4f});
	body[leftUpLeg]->setParent(body[torso]);
	body[leftUpLeg]->setSelfAnchor({0, 1, 0});
	body[leftUpLeg]->setAnchor({0.4, -1, 0});

	body[leftLeg] = new RectangularCuboid(0.3, 1.2, 0.4);
	body[leftLeg]->setColor({0.4f, 0.0f, 0.4f});
	body[leftLeg]->setParent(body[leftUpLeg]);
	body[leftLeg]->setSelfAnchor({0, 1, 0});
	body[leftLeg]->setAnchor({0, -1, 0});

	body[rightUpLeg] = new RectangularCuboid(0.3, 1.2, 0.4);
	body[rightUpLeg]->setColor({0.0f, 0.0f, 0.4f});
	body[rightUpLeg]->setParent(body[torso]);
	body[rightUpLeg]->setSelfAnchor({0, 1, 0});
	body[rightUpLeg]->setAnchor({-0.4, -1, 0});

	body[rightLeg] = new RectangularCuboid(0.3, 1.2, 0.4);
	body[rightLeg]->setColor({0.4f, 0.0f, 0.4f});
	body[rightLeg]->setParent(body[rightUpLeg]);
	body[rightLeg]->setSelfAnchor({0, 1, 0});
	body[rightLeg]->setAnchor({0, -1, 0});
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
	body[head]->setScale(body[head]->getScale() * x);
	body[torso]->setScale(body[torso]->getScale() * x);
	body[rightArm]->setScale(body[rightArm]->getScale() * x);
	body[leftArm]->setScale(body[leftArm]->getScale() * x);
	body[rightForeArm]->setScale(body[rightForeArm]->getScale() * x);
	body[leftForeArm]->setScale(body[leftForeArm]->getScale() * x);
	body[leftUpLeg]->setScale(body[leftUpLeg]->getScale() * x);
	body[rightUpLeg]->setScale(body[rightUpLeg]->getScale() * x);
	body[leftLeg]->setScale(body[leftLeg]->getScale() * x);
	body[rightLeg]->setScale(body[rightLeg]->getScale() * x);
}

void Human::draw(Matrix viewMat)
{
	body[torso]->draw(viewMat);
	body[torso]->drawChildren(viewMat);
}
