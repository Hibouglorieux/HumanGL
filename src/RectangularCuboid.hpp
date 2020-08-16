/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RectangularCuboid.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:52:07 by nathan            #+#    #+#             */
/*   Updated: 2020/08/16 21:31:09 by nathan           ###   ########.fr       */
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
	virtual void drawChildren(Matrix viewMat) override;
	Matrix getModelMat();
	virtual void onNewParent() override; //parent should already be set when this method is called

	void setPos(Vec3 newPos);
	void setRot(Vec3 newRot);
	void setScale(Vec3 newScale);
	void setPos(float x, float y, float z) {setPos({x, y, z});}
	void setRot(float x, float y, float z) {setRot({x, y, z});}
	void setScale(float x, float y, float z) {setScale({x, y, z});}
	void setAnchor(Vec3 newAnchor);
	void setSelfAnchor(Vec3 newSelfAnchor) {selfAnchor = newSelfAnchor;}

	float getWidth() const {return _width;}
	float getHeight() const {return _height;}
	float getDepth() const {return _depth;}

	Vec3 getPos() const {return pos;}
	Vec3 getRot() const {return rot;}
	Vec3 getScale() const {return scale;}
	float posX() const {return _posX;} float posY() const {return _posY;} float posZ() const {return _posZ;}
	float rotX() const {return _rotX;} float rotY() const {return _rotY;} float rotZ() const {return _rotZ;}
	float scaleX() const {return _scaleX;} float scaleY() const {return _scaleY;} float scaleZ() const {return _scaleZ;}
private:
	void updateMatrixes();
    GLuint VAO, VBO;
    Matrix modelMat;
	Matrix transMat, rotMat, scaleMat;// is also the order for matrix mult
	Vec3 pos;
	Vec3 rot;
	Vec3 scale;
	bool hasAnchor;
	Vec3 anchor;//where on parent should be the joint
	Vec3 selfAnchor;//where on itself for parent should be the joint
	float _posX, _posY, _posZ;
	float _rotX, _rotY, _rotZ;
	float _scaleX, _scaleY, _scaleZ;
    Shader shader;
	float _width, _height, _depth;
    std::array<float, 3> color;
	bool shouldUpdateMats;
};

#endif
