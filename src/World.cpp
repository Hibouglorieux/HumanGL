/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   World.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:11:30 by nathan            #+#    #+#             */
/*   Updated: 2020/10/01 03:07:28 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "World.hpp"


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
	for (Object* object : objects)
	{
		object->draw(camera.getMatrix());
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
	currentAnimation++;
	if (currentAnimation >= AnimationHandler::nbOfAnim)
		currentAnimation = 0;
	playAnimation(AnimationHandler::getAnim(currentAnimation));
}

void World::playPrevAnim()
{
	currentAnimation--;
	if (currentAnimation < 0)
		currentAnimation = AnimationHandler::nbOfAnim - 1;
	playAnimation(AnimationHandler::getAnim(currentAnimation));
}
