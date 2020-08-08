/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 19:05:07 by nathan            #+#    #+#             */
/*   Updated: 2020/08/08 22:07:39 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Object.hpp"

#define FOV 60.0f
#define NEAR 0.1f
#define FAR 100.0f

Matrix Object::projMat = Matrix::createProjMatrix(FOV, SCREEN_WIDTH / SCREEN_HEIGHT, NEAR, FAR);


Object::Object( void ) {}
Object::~Object( void ) {}
void Object::setProjMat(Matrix newProjMat)
{
	projMat = newProjMat;	
}
