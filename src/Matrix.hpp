/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:07:43 by nathan            #+#    #+#             */
/*   Updated: 2020/05/25 11:56:33 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MATRIX_CLASS_H
# define MATRIX_CLASS_H
#include <vector>
#include <string>
#include <sstream>
#include <GL/gl.h>

class Matrix {
public:
	Matrix(void);
	Matrix(std::vector<std::vector<float>> dataParam);
	~Matrix(void);
	GLfloat* exportForGL();
	Matrix operator*(const Matrix& rhs);
	void print();
	std::string toString(std::vector<std::vector<float>> dataParam);
private:
	std::vector<std::vector<float>> data;
	std::vector<GLfloat> exportData;
};

#endif
