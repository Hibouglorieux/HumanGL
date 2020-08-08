/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 19:05:09 by nathan            #+#    #+#             */
/*   Updated: 2020/08/08 21:55:11 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef OBJECT_CLASS_H
# define OBJECT_CLASS_H

#include "Utilities.h"
#include "Matrix.hpp"

class Object {
public:
	Object(void);
	virtual void draw(Matrix viewMat) = 0;
	virtual ~Object(void);
	static void setProjMat(Matrix projMat);
protected:
	static Matrix projMat;

};

#endif
