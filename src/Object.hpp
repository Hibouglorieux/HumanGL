/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 19:05:09 by nathan            #+#    #+#             */
/*   Updated: 2020/10/13 09:16:00 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef OBJECT_CLASS_H
# define OBJECT_CLASS_H

#include "Utilities.h"
#include "Matrix.hpp"
#include <vector>
#include <algorithm>

class Object {
public:
	Object(void);
	virtual void draw(Matrix* viewMat) = 0;
	virtual void drawChildren(Matrix* viewMat);
	virtual ~Object(void);
	virtual Vec3 getPos() const = 0;
	static void setProjMat(Matrix projMat);
	void addChild(Object* newchild);
	void removeChild(Object* child);
	void setParent(Object* parent);
	void setID(std::string newID);
	std::string getID() const;
	virtual void onNewParent() {};
	Object* getParent();
	std::vector<Object*> getChildren() {return children;}
protected:
	std::string ID;
	std::vector<Object*> children;
	Object* parent;
	static Matrix projMat;
};

#endif
