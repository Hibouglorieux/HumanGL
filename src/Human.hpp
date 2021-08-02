/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Human.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 21:11:34 by nathan            #+#    #+#             */
/*   Updated: 2020/10/22 12:46:51 by nathan           ###   ########.fr       */
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
	virtual void draw(Matrix* viewMat) override;
	virtual void draw(Matrix* viewMat, Shader* specialEffect, std::vector<std::tuple<std::function<void(GLint, GLsizei, const GLfloat*)>, std::string, const GLfloat*>> shaderData) override;
	void setPos(float x, float y, float z);
	void setPos(Vec3 pos) {setPos(pos.x, pos.y, pos.z);};
	Vec3 getPos() const;
	void setRot(float x, float y, float z);
	void setScale(float x);
	void playAnimation(bvhData newAnim);
	void cancelAnimation();
	void update();
	RectangularCuboid* getBodyPart(Body bodyPart);
	~Human(void);
private:
	Vec3 pos;
	std::vector<RectangularCuboid*> body;
	int frameCount;
	bvhData animation;
};

#endif
