/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Skeleton.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 05:32:43 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/05/26 05:32:43 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Skeleton.hpp>
#include <fstream>
#include <string>
#include <sstream>
#include "Matrix.hpp"
#include "Window.hpp"
#include "math.h"

vector<vector<float>> Skeleton::motion;

void Skeleton::init() {
	int numFrames;
	string line;

	Cube::init();
	ifstream file("motion.bvh");
	do {getline(file, line);} while (line.find("MOTION")==string::npos);
	file.ignore(8);
	file >> numFrames; file.ignore('\n');
	cout << "num frames: " << numFrames <<endl;
	getline(file, line);
	while (numFrames--) {
		vector<float> frame;
		getline(file, line);
		stringstream s(line);
		float value;
		while (s >> value)
			frame.push_back(value);
		motion.push_back(frame);
	}
}

void Skeleton::draw() {
	static int frame = 0;
	Matrix mat, t, rx, ry, rz;

	glfwSetWindowTitle(Window::getWindow(), ("frame " + to_string(frame)).c_str());
	Matrix viewMat = Matrix::createTranslationMatrix(0, 0, -200); // view mat
#define RED {1, 0, 0}
#define GREEN {0, 1, 0}
#define BLUE {0, 0, 1}

	// Chest
	mat = Matrix();
	mat = mat * viewMat;
	mat = mat * Matrix::createTranslationMatrix(motion[frame][0], motion[frame][1], motion[frame][2]);
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][3]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][4]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][5]);
	mat = mat * rx * ry * rz;
#define CHEST_HEIGHT 32
	mat = mat * Matrix::createTranslationMatrix(0, CHEST_HEIGHT/2, 0);
	mat = mat * Matrix::createScaleMatrix(12, CHEST_HEIGHT, 10);
	Cube::draw(mat.exportForGL(), GREEN);

	// forearm
	mat = Matrix();
	mat = mat * viewMat;
	mat = mat * Matrix::createTranslationMatrix(motion[frame][0], motion[frame][1], motion[frame][2]);
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][3]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][4]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][5]);
	mat = mat * rx * ry * rz;
	mat = mat * Matrix::createTranslationMatrix(10, CHEST_HEIGHT/2+10, 0);
#define ARM_LEN 20
	int i = 6 * 2;
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][i+3]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][i+4]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][i+5]);
	mat = mat * rx * ry * rz;
	mat = mat * Matrix::createTranslationMatrix(0, ARM_LEN/2, 0);
	mat = mat * Matrix::createScaleMatrix(5, ARM_LEN, 5);
	Cube::draw(mat.exportForGL(), GREEN);

	// forearm
	mat = Matrix();
	mat = mat * viewMat;
	mat = mat * Matrix::createTranslationMatrix(motion[frame][0], motion[frame][1], motion[frame][2]);
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][3]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][4]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][5]);
	mat = mat * rx * ry * rz;
	mat = mat * Matrix::createTranslationMatrix(-10, CHEST_HEIGHT/2+10, 0);
	i = 6 * 5;
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][i+3]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][i+4]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][i+5]);
	mat = mat * rx * ry * rz;
	mat = mat * Matrix::createTranslationMatrix(0, ARM_LEN/2, 0);
	mat = mat * Matrix::createScaleMatrix(5, ARM_LEN, 5);
	Cube::draw(mat.exportForGL(), GREEN);

	frame = (frame+1) % motion.size();
}
