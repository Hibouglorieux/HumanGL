/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Human.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 21:11:34 by nathan            #+#    #+#             */
/*   Updated: 2020/08/16 21:47:55 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RectangularCuboid.hpp"

#ifndef HUMAN_CLASS_H
# define HUMAN_CLASS_H

// TODO handle copy
class Human {
public:
	Human(void);
	void draw(Matrix viewMat);
	void setPos(float x, float y, float z){torso->setPos(x, y, z);}
	void setRot(float x, float y, float z){torso->setRot(x, y, z);}
	void setScale(float x, float y, float z);
	~Human(void);
private:
	RectangularCuboid *head, *torso, *rightArm, *leftArm, *rightForeArm, *leftForeArm, *leftThigh, *rightThigh, *leftLeg, *rightLeg;// maybe stack instead ?
};

#endif
