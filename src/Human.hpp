/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Human.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 21:11:34 by nathan            #+#    #+#             */
/*   Updated: 2020/09/02 01:31:08 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RectangularCuboid.hpp"
#include "Object.hpp"
#include <vector>

#ifndef HUMAN_CLASS_H
# define HUMAN_CLASS_H

// TODO handle copy
class Human : public Object{
public:
	enum Body : int {
		chest = 0, head, leftArm, leftForeArm, rightArm, rightForeArm,
		leftUpLeg, leftLeg, rightUpLeg, rightLeg
	};
	Human(void);
	virtual void draw(Matrix viewMat) override;
	void setPos(float x, float y, float z){body[chest]->setPos(x, y, z);}
	void setRot(float x, float y, float z){body[chest]->setRot(x, y, z);}
	void setScale(float x);
	~Human(void);
private:
	std::vector<RectangularCuboid*> body;
};

#endif
