/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   World.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:11:54 by nathan            #+#    #+#             */
/*   Updated: 2020/10/12 14:33:08 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef WORLD_CLASS_H
# define WORLD_CLASS_H

#include "Object.hpp"
#include "Camera.hpp"
#include "AnimationHandler.hpp"
#include "Human.hpp"

class World {
public:
	World( void );
	virtual ~World( void );
	void render( void );
	void addObject(Object* newobj);
	std::vector<Object*>& getObjects();
	void setCamera(Camera newCamera);
	void playAnimation(bvhData animation);
	void cancelAnimation();
	void playNextAnim();
	void playPrevAnim();
	void addHuman();
	void clearObject(std::string ID);
	Camera& getCamera();
private:
	static int i;
	void onEnterAnim();
	void onLeaveAnim();
	int currentAnimation;
	Camera camera;
	std::vector<Object*> objects;
};

#endif
