/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 19:17:30 by nathan            #+#    #+#             */
/*   Updated: 2020/08/08 19:40:24 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_HPP
#define CUBE_HPP

#include <iostream>
#include <array>
#include "Vec3.hpp"
#include "RectangularCuboid.hpp"

class Cube : public RectangularCuboid {
public:
	Cube(float size, Matrix modelMat = {});
	virtual ~Cube(void) {}
private:
};

#endif
