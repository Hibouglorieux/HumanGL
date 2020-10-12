/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Human.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 21:11:34 by nathan            #+#    #+#             */
/*   Updated: 2020/10/12 12:54:43 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RectangularCuboid.hpp"
#include "Object.hpp"
#include <vector>
#include "bvhParser.hpp"

#ifndef HUMAN_CLASS_H
# define HUMAN_CLASS_H

// TODO handle copy
enum Body : int {
	chest = 0, head, leftArm, leftForeArm, rightArm, rightForeArm,
	leftUpLeg, leftLeg, rightUpLeg, rightLeg
};
class Human : public Object{
public:
	static const int nbOfLimbs;
	Human(void);
	virtual void draw(Matrix viewMat) override;
	void setPos(float x, float y, float z);
	void setPos(Vec3 pos) {setPos(pos.x, pos.y, pos.z);};
	Vec3 getPos() const;
	void setRot(float x, float y, float z);
	void setScale(float x);
	void playAnimation(bvhData newAnim);
	void cancelAnimation();
	RectangularCuboid* getBodyPart(Body bodyPart);
	~Human(void);
private:
	Vec3 pos;
	std::vector<RectangularCuboid*> body;
	int frameCount;
	bvhData animation;
};

#endif
