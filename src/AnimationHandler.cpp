/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimationHandler.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 00:27:43 by nathan            #+#    #+#             */
/*   Updated: 2020/10/01 03:25:09 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AnimationHandler.hpp"

const std::vector<bvhData> AnimationHandler::animations =
{
	bvhParser::loadFile("Animations/walk.bvh"),
	bvhParser::loadFile("Animations/jump.bvh"),
	bvhParser::loadFile("Animations/robot-dance.bvh"),
	bvhParser::loadFile("Animations/robot-dance2.bvh"),
	bvhParser::loadFile("Animations/dance.bvh"),
	bvhParser::loadFile("Animations/breakdance.bvh"),
	bvhParser::loadFile("Animations/dying.bvh"),
	bvhParser::loadFile("Animations/baseball.bvh"),
	bvhParser::loadFile("Animations/falling.bvh"),
	bvhParser::loadFile("Animations/in-water.bvh"),
	bvhParser::loadFile("Animations/climbing.bvh"),
};

const int AnimationHandler::nbOfAnim = animations.size();

bvhData AnimationHandler::getAnim(int i)
{
	if (i >= nbOfAnim || i < 0)
		std::cerr << "Error: received incorrect int with value: " << i << std::endl;
	return animations.at(i);
}
