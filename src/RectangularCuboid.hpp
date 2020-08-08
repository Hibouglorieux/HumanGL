/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RectangularCuboid.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:52:07 by nathan            #+#    #+#             */
/*   Updated: 2020/08/08 19:39:57 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RECTANGULARCUBOID_CLASS_H
# define RECTANGULARCUBOID_CLASS_H
#include "Object.hpp"
#include <array>
#include "Shader.hpp"
#include "Matrix.hpp"

class RectangularCuboid : public Object {
public:
	RectangularCuboid(void);
	virtual ~RectangularCuboid( void );
	RectangularCuboid(float width, float height, float depth, Matrix modelMatrix = {});
    void setModelMat(Matrix newModelMat);
	void setColor(std::array<float, 3> Color);
	virtual void draw(Matrix viewMat) override;
private:
    GLuint VAO, VBO, EBO;
    Matrix modelMat;
    Shader shader;
    std::array<float, 3> color;
};

#endif
