/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 19:05:07 by nathan            #+#    #+#             */
/*   Updated: 2020/10/12 14:09:05 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Object.hpp"

#define FOV 60.0f
#define NEAR 0.1f
#define FAR 100.0f

Matrix Object::projMat = Matrix::createProjMatrix(FOV, SCREEN_WIDTH / SCREEN_HEIGHT, NEAR, FAR);


Object::Object( void )
{
	parent = nullptr;
}

Object::~Object( void )
{
	if (parent)
		parent->removeChild(this);
	for (Object* child : children)
	{
		child->parent = nullptr;
	}
}

void Object::setProjMat(Matrix newProjMat)
{
	projMat = newProjMat;	
}

void Object::drawChildren(Matrix viewMat)
{
	for (auto child : this->getChildren())
	{
		child->draw(viewMat);
		child->drawChildren(viewMat);
	}
}

void Object::addChild(Object* newchild)
{
	if (std::find(children.begin(), children.end(), newchild) == children.end())
	{
		std::cout << "Warning : adding already existing child" << std::endl;
		return ;
	}
	children.push_back(newchild);
	newchild->parent = this;
	newchild->onNewParent();
}

void Object::removeChild(Object* child)
{
	children.erase(std::find(children.begin(), children.end(), child));
	child->parent = nullptr;
}

void Object::setParent(Object* parent)
{
	this->parent = parent;
	parent->children.push_back(this);
	this->onNewParent();
}

Object* Object::getParent()
{
	return (this->parent);
}

void Object::setID(std::string newID)
{
	ID = newID;
}

std::string Object::getID() const
{
	return ID;
}
