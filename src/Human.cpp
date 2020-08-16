/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Human.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 21:11:31 by nathan            #+#    #+#             */
/*   Updated: 2020/08/16 21:47:40 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Human.hpp"

Human::Human()
{
	torso = new RectangularCuboid(1, 2, 0.8);
	torso->setColor({1.0f, 0.0f, 0.0f});

	head = new RectangularCuboid(0.6, 0.6, 0.6);
	head->setColor({1.0f, 0.0f, 1.0f});
	head->setParent(torso);
	head->setAnchor({0, 1, 0});
	head->setSelfAnchor({0, -1, 0});


	rightArm = new RectangularCuboid(0.2, 1, 0.2);
	rightArm->setColor({0.0f, 0.0f, 1.0f});
	rightArm->setSelfAnchor({1, 1, 0});
	rightArm->setParent(torso);
	rightArm->setAnchor({-1, 0.9f, 0});

	rightForeArm = new RectangularCuboid(0.2, 1, 0.2);
	rightForeArm->setColor({0.0f, 0.2f, 0.7f});
	rightForeArm->setSelfAnchor({0, 1, 0});
	rightForeArm->setParent(rightArm);
	rightForeArm->setAnchor({0, -1, 0});

	leftArm = new RectangularCuboid(0.2, 1, 0.2);
	leftArm->setColor({0.0f, 0.0f, 1.0f});
	leftArm->setSelfAnchor({-1, 1, 0});
	leftArm->setParent(torso);
	leftArm->setAnchor({1, 0.9f, 0});

	leftForeArm = new RectangularCuboid(0.2, 1, 0.2);
	leftForeArm->setColor({0.0f, 0.2f, 0.7f});
	leftForeArm->setSelfAnchor({0, 1, 0});
	leftForeArm->setParent(leftArm);
	leftForeArm->setAnchor({0, -1, 0});

	leftThigh = new RectangularCuboid(0.3, 1.2, 0.4);
	leftThigh->setColor({0.0f, 0.0f, 0.4f});
	leftThigh->setParent(torso);
	leftThigh->setSelfAnchor({0, 1, 0});
	leftThigh->setAnchor({0.4, -1, 0});

	leftLeg = new RectangularCuboid(0.3, 1.2, 0.4);
	leftLeg->setColor({0.4f, 0.0f, 0.4f});
	leftLeg->setParent(leftThigh);
	leftLeg->setSelfAnchor({0, 1, 0});
	leftLeg->setAnchor({0, -1, 0});

	rightThigh = new RectangularCuboid(0.3, 1.2, 0.4);
	rightThigh->setColor({0.0f, 0.0f, 0.4f});
	rightThigh->setParent(torso);
	rightThigh->setSelfAnchor({0, 1, 0});
	rightThigh->setAnchor({-0.4, -1, 0});

	rightLeg = new RectangularCuboid(0.3, 1.2, 0.4);
	rightLeg->setColor({0.4f, 0.0f, 0.4f});
	rightLeg->setParent(rightThigh);
	rightLeg->setSelfAnchor({0, 1, 0});
	rightLeg->setAnchor({0, -1, 0});
}

Human::~Human()
{
	delete head;
	delete torso;
	delete rightArm;
	delete leftArm;
	delete rightForeArm;
	delete leftForeArm;
	delete leftThigh;
	delete rightThigh;
	delete leftLeg;
	delete rightLeg;
}

void Human::setScale(float x, float y, float z)
{
	Vec3 newScale(x, y, z);

	head->setScale(newScale);
	torso->setScale(newScale);
	rightArm->setScale(newScale);
	leftArm->setScale(newScale);
	rightForeArm->setScale(newScale);
	leftForeArm->setScale(newScale);
	leftThigh->setScale(newScale);
	rightThigh->setScale(newScale);
	leftLeg->setScale(newScale);
	rightLeg->setScale(newScale);
}

void Human::draw(Matrix viewMat)
{
	torso->draw(viewMat);
	torso->drawChildren(viewMat);
}
