/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   World.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:11:30 by nathan            #+#    #+#             */
/*   Updated: 2020/10/12 15:36:57 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "World.hpp"

int World::i = 1;

World::World()
{
	currentAnimation = 0;
	std::vector<Object*> objects = {};
}

World::~World()
{
	objects.clear();
}

void World::render()
{
	Matrix viewMat = camera.getMatrix();
	for (Object* object : objects)
	{
		object->draw(&viewMat);
	}
}


void World::addObject(Object* newobj)
{
	objects.push_back(newobj);
}

std::vector<Object*>& World::getObjects()
{
	return objects;
}

void World::setCamera(Camera newCamera)
{
	camera= newCamera;
}

Camera& World::getCamera()
{
	return camera;
}

void World::playAnimation(bvhData animation)
{
	for (Object* obj : objects)
	{
		Human* human = dynamic_cast<Human*>(obj);
		if (human)
			human->playAnimation(animation);
	}
}

void World::cancelAnimation()
{
	for (Object* obj : objects)
	{
		Human* human = dynamic_cast<Human*>(obj);
		if (human)
			human->cancelAnimation();
	}
	currentAnimation = 0;
}

void World::playNextAnim()
{
	onLeaveAnim();
	currentAnimation++;
	onEnterAnim();
	if (currentAnimation >= AnimationHandler::nbOfAnim)
		currentAnimation = 0;
	playAnimation(AnimationHandler::getAnim(currentAnimation));
}

void World::playPrevAnim()
{
	onLeaveAnim();
	currentAnimation--;
	onEnterAnim();
	if (currentAnimation < 0)
		currentAnimation = AnimationHandler::nbOfAnim - 1;
	playAnimation(AnimationHandler::getAnim(currentAnimation));
}

void World::onLeaveAnim()//TODO
{
	return;
	if (currentAnimation == BREAKDANCE)
	{
		for (Object* obj : objects)
		{
			Human* human = dynamic_cast<Human*>(obj);
			if (human)
			{
				Vec3 position = human->getPos();
				position.y += 2.7;
				human->setPos(position);
			}
		}
	}
}

void World::onEnterAnim()//TODO
{
	return;
	if (currentAnimation == 1)
	{
		Human* human = new Human();
		human->setPos(4, 4.9f, 0);
		human->setID("tmpHuman");
		addObject(human);
	}
	if (currentAnimation == BREAKDANCE)
	{
		for (Object* obj : objects)
		{
			Human* human = dynamic_cast<Human*>(obj);
			if (human)
			{
				Vec3 position = human->getPos();
				position.y -= 2.7;
				human->setPos(position);
			}
		}
	}
}

void World::addHuman()
{
	Human* human = new Human();
	human->setPos((i % 3 == 2 ? -1 : i % 3) * 4
			, 4.9f, i / 3 * -5);
	i++;
	human->setID("tmpHuman");
	addObject(human);
}

void World::clearObject(std::string ID)
{
	for (Object*& obj : objects)
	{
		if (obj->getID() == ID)
		{
			delete obj;
			obj = nullptr;
		}
	}
	objects.erase(std::remove(objects.begin(), objects.end(), nullptr), objects.end());
	i = 1;
}
