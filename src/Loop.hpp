/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Loop.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 15:40:30 by nathan            #+#    #+#             */
/*   Updated: 2020/09/02 01:27:10 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LOOP_CLASS_H
# define LOOP_CLASS_H

#include <vector>
#include "World.hpp"

class Loop {
public:
	static void loop();
	static void addObject(Object* newobj);
	static void setWorld(World* newWorld) {world = newWorld;};
private:
	static void processInput();
	static bool shouldStop;
	static double frameTime;
	const static double refreshingRate;
	static std::vector<Object*> objects;
	static World* world;
};

#endif
