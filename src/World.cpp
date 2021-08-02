/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   World.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:11:30 by nathan            #+#    #+#             */
/*   Updated: 2021/08/02 15:53:57 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "World.hpp"
#include <array>

int World::i = 1;

World::World()
{
	currentAnimation = 0;
	std::vector<Object*> objects = {};
}

World::~World()
{
	for (auto it : objects)
	{
		delete it;
	}
	objects.clear();
}

void World::render()
{
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);

		glEnable(GL_DEPTH_TEST);


	Matrix viewMat = camera.getMatrix();
	for (Object* object : objects)
	{
		object->draw(&viewMat);
	}

		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glDisable(GL_DEPTH_TEST);

	std::array<float, 3> color = {0.0f, 0.0f, 0.0f};
	Shader specialEffect("new.vert", "outline.frag");
	std::vector<std::tuple<std::function<void(GLint, GLsizei, const GLfloat*)>, std::string, const GLfloat*>> shaderData;
	std::tuple<std::function<void(GLint, GLsizei, const GLfloat*)>, std::string, const GLfloat*> functionCall = std::make_tuple(glUniform3fv, "myColor", &color.front());
	shaderData.push_back(functionCall);
	for (Object* object : objects)
	{
		Human* human = dynamic_cast<Human*>(object);
		if (human)
		{
			human->setScale(1.2f);
			human->draw(&viewMat, &specialEffect, shaderData);
			human->setScale(1 / 1.2f);
		}
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
