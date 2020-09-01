/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 01:10:29 by nathan            #+#    #+#             */
/*   Updated: 2020/09/02 01:30:37 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"

Camera::Camera() : Camera(Vec3(0, -2, -10))
{
}

Camera::Camera(float x, float y, float z) : Camera(Vec3(x, y, z))
{
}

Camera::Camera(Vec3 translation)
{
	this->translation = translation;
	this->view = Matrix::createTranslationMatrix(Vec3(translation.x, translation.y, translation.z));
}

Matrix Camera::getMatrix()
{
	return view;
}
