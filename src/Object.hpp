/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 19:05:09 by nathan            #+#    #+#             */
/*   Updated: 2020/08/16 04:30:20 by nathan           ###   ########.fr       */
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
	virtual void draw(Matrix viewMat) = 0;
	virtual ~Object(void);
	static void setProjMat(Matrix projMat);
	void addChild(Object* newchild);
	void removeChild(Object* child);
	void setParent(Object* parent);
	virtual void onNewParent() = 0;
	Object* getParent();
protected:
	std::vector<Object*> children;
	Object* parent;
	static Matrix projMat;
};

#endif
