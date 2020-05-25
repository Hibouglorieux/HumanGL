/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:07:40 by nathan            #+#    #+#             */
/*   Updated: 2020/05/25 12:16:12 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Matrix.hpp"
#include "Utilities.h"

Matrix::Matrix( void )
{
	data = {
		{1, 0, 0, 0,},
		{0, 1, 0, 0,},
		{0, 0, 1, 0,},
		{0, 0, 0, 1}
	};
}

Matrix::Matrix(std::vector<std::vector<float>> dataParam)
{
	size_t i = 0;
	while (i < dataParam.size())
	{
		M_Assert(dataParam[i].size() == 4, ("Error: wrong size of matrix given as constructor (it is not 4x4)\n" + toString(dataParam)).c_str());
		i++;
	}
	data = dataParam;
}

std::string Matrix::toString(std::vector<std::vector<float>> dataParam)
{
	std::stringstream ss;
	ss.precision(2); // print only 2 first decimals
	ss << std::fixed; // put precision for 0.00 too
	for (size_t i = 0; i < dataParam.size(); i++)
	{
		ss << "{";
		for (size_t j = 0; j < dataParam[i].size(); j++)
		{
			ss.width(4);
			ss << " " << dataParam[i][j];
		}
		ss << " }";
		ss << std::endl;
	}
	return ss.str();
}

void Matrix::print()
{
	std::cout << toString(data) << std::endl;
}

Matrix::~Matrix()
{
}

GLfloat*	Matrix::exportForGL()
{
	int i;

	i = 0;
	while (i < 4)
	{
		exportData[i * 4 + 0] = (GLfloat)data[i][0];
		exportData[i * 4 + 1] = (GLfloat)data[i][1];
		exportData[i * 4 + 2] = (GLfloat)data[i][2];
		exportData[i * 4 + 3] = (GLfloat)data[i][3];
		i++;
	}
	return exportData.data();
}

Matrix Matrix::operator*(const Matrix& rhs)
{
	int firstRow = 0;
	int firstColumn = 0;
	int secondColumn = 0;

	std::vector<std::vector<float>> newMatrixData;
	firstRow = 0;
	while (firstRow < 4)
	{
		firstColumn = 0;
		while (firstColumn < 4)
		{
			secondColumn = 0;
			while (secondColumn < 4)
			{
				newMatrixData[firstRow][firstColumn] += this->data[firstRow][secondColumn] * rhs.data[secondColumn][firstColumn];
				secondColumn++;
			}
			firstColumn++;
		}
		firstRow++;
	}
	return Matrix(newMatrixData);
}
