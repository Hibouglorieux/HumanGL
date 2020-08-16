/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RectangularCuboid.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:52:07 by nathan            #+#    #+#             */
/*   Updated: 2020/08/16 05:33:28 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RECTANGULARCUBOID_CLASS_H
# define RECTANGULARCUBOID_CLASS_H
#include "Object.hpp"
#include <array>
#include "Shader.hpp"
#include "Matrix.hpp"

#define TRANS_MAT 0
#define ROT_MAT 1
#define SCALE_MAT 2

class RectangularCuboid : public Object {
public:
	RectangularCuboid(void);
	virtual ~RectangularCuboid( void );
	RectangularCuboid(float width, float height, float depth);
    void setMat(Matrix newMat, int type);
	void setColor(std::array<float, 3> Color);
	virtual void draw(Matrix viewMat) override;
	Matrix getModelMat();
	virtual void onNewParent() override; //parent should already be set when this method is called
	float getWidth() {return _width;}
	float getHeight() {return _height;}
	float getDepth() {return _depth;}
private:
	void updateMatrixes();
    GLuint VAO, VBO;
    Matrix modelMat;
	Matrix transMat, rotMat, scaleMat;// is also the order for matrix mult
    Shader shader;
	float _width, _height, _depth;
    std::array<float, 3> color;
	bool shouldUpdateMats;
};

#endif
