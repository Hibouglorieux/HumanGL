/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Human.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 21:11:34 by nathan            #+#    #+#             */
/*   Updated: 2020/08/17 21:18:32 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RectangularCuboid.hpp"
#include <vector>

#ifndef HUMAN_CLASS_H
# define HUMAN_CLASS_H

// TODO handle copy
class Human {
public:
	enum Body : int {
		torso = 0, head, rightArm, leftArm, rightForeArm, leftForeArm, leftUpLeg,
		rightUpLeg, leftLeg, rightLeg
	};
	Human(void);
	void draw(Matrix viewMat);
	void setPos(float x, float y, float z){body[torso]->setPos(x, y, z);}
	void setRot(float x, float y, float z){body[torso]->setRot(x, y, z);}
	void setScale(float x);
	~Human(void);
	std::vector<RectangularCuboid*> body;
private:
};

#endif
