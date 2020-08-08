/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 19:17:19 by nathan            #+#    #+#             */
/*   Updated: 2020/08/08 20:19:07 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube.hpp"

Cube::Cube(float size, Matrix modelMat) : RectangularCuboid(size, size, size, modelMat)
{
}
