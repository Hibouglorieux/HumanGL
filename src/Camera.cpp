/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 01:10:29 by nathan            #+#    #+#             */
/*   Updated: 2020/10/01 02:52:23 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"
#include "Utilities.h"

#define X_ROTATION_SPEED 1
#define Y_ROTATION_SPEED 1

Camera::Camera() : Camera(Vec3(0, 4, 10))
{
}

Camera::Camera(float x, float y, float z) : Camera(Vec3(x, y, z))
{
}

Camera::Camera(Vec3 position)
{
	this->pos = position;
	hasTarget = false;
	dir = {0, 0, 0};
	actualizeView();
}

Matrix Camera::getMatrix()
{
	return view;
}

void Camera::lookAt(Vec3 target)
{
	hasTarget = true;
	this->target = target;
}

void Camera::move(bool forward, bool backward, bool right, bool left, float speedFactor)
{
	if (!forward && !backward && !right && !left)
		return;
	Vec3 moveDir;
	moveDir.z = -cos(TO_RAD(dir.y)) * cos(TO_RAD(dir.x));
	moveDir.y = -sin(TO_RAD(dir.x));
	moveDir.x = sin(TO_RAD(dir.y)) * cos(TO_RAD(dir.x));
	Vec3 realMovement;
	if (forward)
		realMovement = moveDir;
	if (backward)
		realMovement -= moveDir;
	moveDir.y = 0;
	if (right)
	{
		realMovement += Matrix::createRotationMatrix(Matrix::RotationDirection::Y, 90) * moveDir;
	}
	if (left)
	{
		realMovement += Matrix::createRotationMatrix(Matrix::RotationDirection::Y, -90) * moveDir;
	}
	pos += realMovement.getNormalized() * speedFactor;
	if (realMovement != Vec3::ZERO)
	actualizeView();
}

void Camera::moveUp(float distance)
{
	pos.y += distance;
	actualizeView();
}

void Camera::moveDown(float distance)
{
	pos.y -= distance;
	actualizeView();
}

void Camera::rotate(double x, double y)
{
	if (x == 0 && y == 0)
		return;
	dir.y += x;
	dir.x += y;
	if (dir.x > 89.0f)
		dir.x = 89;
	if (dir.x < -89.0f)
		dir.x = -89.0f;
	actualizeView();
}

void Camera::actualizeView()
{
	if (hasTarget)
	{

	}
	else
	{
		rotMat = Matrix::createRotationMatrix(Matrix::RotationDirection::X, dir.x);
		rotMat *= Matrix::createRotationMatrix(Matrix::RotationDirection::Y, dir.y);
		this->view = rotMat * Matrix::createTranslationMatrix(-pos);
	}
}
