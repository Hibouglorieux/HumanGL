/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RectangularCuboid.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:52:07 by nathan            #+#    #+#             */
/*   Updated: 2020/09/02 12:51:07 by nathan           ###   ########.fr       */
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
	RectangularCuboid(void); // TODO add copy constructor
	virtual ~RectangularCuboid( void );
	RectangularCuboid(float width, float height, float depth);
    void setMat(Matrix newMat, int type);
	void setColor(std::array<float, 3> Color);
	virtual void draw(Matrix viewMat) override;
	Matrix getModelMat();
	Matrix getParentMatrix();
	virtual void onNewParent() override; //parent should already be set when this method is called

	void setPos(Vec3 newPos);
	void setRot(Vec3 newRot);
	void setScale(Vec3 newScale);
	void setPos(float x, float y, float z) {setPos({x, y, z});}
	void setRot(float x, float y, float z) {setRot({x, y, z});}
	void setScale(float x, float y, float z) {setScale({x, y, z});}
	void setSelfAnchor(Vec3 newSelfAnchor) {selfAnchor = newSelfAnchor; shouldUpdateMats = true;}
	void pouet(){transMat.print();}
	void setInitialRot(Vec3 newInitialRot){initialRot = newInitialRot;}
	Vec3 getRelativePos(Vec3 anchor);

	bool debug;

	Vec3 getPos() const {return pos;}
	Vec3 getRot() const {return rot;}
	Vec3 getScale() const {return scale;}
private:
	void updateMatrixes();
    GLuint VAO, VBO;//TODO change to static ?
    Matrix modelMat, myMat;
	Matrix transMat, rotMat, scaleMat;// is also the order for matrix mult
	Vec3 pos;
	Vec3 rot;
	Vec3 initialRot;
	Vec3 scale;
	Vec3 selfAnchor;//where is the joint on itself
    Shader shader;
    std::array<float, 3> color;
	bool shouldUpdateMats;
};

#endif
