/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   World.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:11:54 by nathan            #+#    #+#             */
/*   Updated: 2020/09/02 01:25:22 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef WORLD_CLASS_H
# define WORLD_CLASS_H

#include "Object.hpp"
#include "Camera.hpp"

class World {
public:
	World( void );
	virtual ~World( void );
	void render( void );
	void addObject(Object* newobj);
	std::vector<Object*>& getObjects();
	void setCamera(Camera newCamera);
	Camera& getCamera();
private:
	Camera camera;
	std::vector<Object*> objects;
};

#endif
