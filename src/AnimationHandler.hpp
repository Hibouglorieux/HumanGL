/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimationHandler.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 00:27:45 by nathan            #+#    #+#             */
/*   Updated: 2021/08/02 15:19:37 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ANIMATIONHANDLER_CLASS_H
# define ANIMATIONHANDLER_CLASS_H

#include "bvhParser.hpp"

class AnimationHandler {
public:
	static bvhData getAnim(int i);
	static const int nbOfAnim;
private:
	static const std::vector<bvhData> animations;
};

#endif
