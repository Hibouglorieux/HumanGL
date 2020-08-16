/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:07:40 by nathan            #+#    #+#             */
/*   Updated: 2020/08/16 19:34:38 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Matrix.hpp"
#include "Utilities.h"

/*
constexpr std::vector<std::vector<float>> Matrix::Projection = {
	float tanHalfFov = tan(to_rad(fov) / 2); = {
		{1 / (aspect * tanHalfFov), 0 , 0, 0},
		{0, 1 / tanHalfFov, 0, 0},
		{0, 0 , -(far + near) / (far - near), (-2 * far * near) / (far - near)},
		{0, 0 , -1, 1}}
};
*/

Matrix::Matrix( void )
{
	data = {
		{1, 0, 0, 0,},
		{0, 1, 0, 0,},
		{0, 0, 1, 0,},
		{0, 0, 0, 1}
	};
}

Matrix::Matrix( std::vector<std::vector<float>> dataParam )
{
	size_t i = 0;
	while ( i < dataParam.size() )
	{
		M_Assert( dataParam[i].size() == 4, ( "Error: wrong size of matrix given as constructor (it is not 4x4)\n" + toString(dataParam) ).c_str() );
		i++;
	}
	data = dataParam;
}

Matrix::Matrix( const Matrix& copy )
{
	data = copy.data;
}

Matrix Matrix::createProjMatrix( float fov, float aspect, float near, float far )
{
	float tanHalfFov = tan( TO_RAD(fov) / 2 );
	Matrix projMatrix({
		{1 / ( aspect * tanHalfFov ), 0 , 0, 0},
		{0, 1 / tanHalfFov, 0, 0},
		{0, 0 , -( far + near ) / ( far - near ), ( -2 * far * near ) / ( far - near )},
		{0, 0 , -1, 1}});
	return std::move( projMatrix );
}

Matrix Matrix::createTranslationMatrix( float x, float y, float z )
{
	Matrix translationMatrix({
			{1, 0, 0, x},
			{0, 1, 0, y},
			{0, 0, 1, z},
			{0, 0, 0, 1}});
	return std::move( translationMatrix );
}

Matrix Matrix::createScaleMatrix( float x, float y, float z )
{
	Matrix scaleMatrix({
			{x, 0, 0, 0},
			{0, y, 0, 0},
			{0, 0, z, 0},
			{0, 0, 0, 1}});
	return std::move( scaleMatrix );
}

Matrix Matrix::createRotationMatrix( RotationDirection dir, float angle )
{
	Matrix rotationMatrix;
	angle = TO_RAD(angle);
	if ( dir == RotationDirection::X )
	{
		rotationMatrix = Matrix({
			{1,     0,            0,       0},
			{0, cosf(angle), -sinf(angle), 0},
			{0, sinf(angle),  cosf(angle), 0},
			{0,     0,            0,       1}
		});
	}
	if ( dir == RotationDirection::Y )
	{
		rotationMatrix = Matrix({
			{ cosf(angle), 0, sinf(angle), 0},
			{    0,        1,      0,      0},
			{-sinf(angle), 0, cosf(angle), 0},
			{    0,        0,      0,      1}
		});
	}
	if ( dir == RotationDirection::Z )
	{
		rotationMatrix = Matrix({
			{cosf(angle), -sinf(angle), 0, 0},
			{sinf(angle),  cosf(angle), 0, 0},
			{    0,            0,       1, 0},
			{    0,            0,       0, 1}
		});
	}
	return std::move( rotationMatrix );
}


std::string Matrix::toString( std::vector<std::vector<float>> dataParam ) const
{
	std::stringstream ss;
	ss.precision(2); // print only 2 first decimals
	ss << std::fixed; // put precision for 0.00 too
	for ( size_t i = 0; i < dataParam.size(); i++ )
	{
		ss << "{";
		for ( size_t j = 0; j < dataParam[i].size(); j++ )
		{
			ss.width(4);
			ss << " " << dataParam[i][j];
		}
		ss << " }";
		ss << std::endl;
	}
	return ss.str();
}

void Matrix::print() const
{
	std::cout << toString( data ) << std::endl;
}

Vec3 Matrix::vectorMult(const Vec3 vec) const
{
	Vec3 newVec;
	
		for (int j = 0; j < 3; j++)
		{
			float v = j == 0 ? vec.x : j == 1 ? vec.y : vec.z;
			newVec.x += this->data[0][j] * v;
			newVec.y += this->data[1][j] * v;
			newVec.z += this->data[2][j] * v;
		}
	return newVec;
}

Matrix::~Matrix()
{
}

GLfloat*	Matrix::exportForGL()
{
	exportData.resize(16);
	int i;

	i = 0;
	while ( i < 4 )
	{
		exportData[i * 4 + 0] = (GLfloat)data[i][0];
		exportData[i * 4 + 1] = (GLfloat)data[i][1];
		exportData[i * 4 + 2] = (GLfloat)data[i][2];
		exportData[i * 4 + 3] = (GLfloat)data[i][3];
		i++;
	}
	return exportData.data();
}

Matrix Matrix::operator*( const Matrix& rhs ) const
{
	int firstRow = 0;
	int firstColumn = 0;
	int secondColumn = 0;

	Matrix newMatrix( { {0, 0, 0, 0},
						{0, 0, 0, 0},
						{0, 0, 0, 0},
						{0, 0, 0, 0} });
	firstRow = 0;
	while ( firstRow < 4 )
	{
		firstColumn = 0;
		while ( firstColumn < 4 )
		{
			secondColumn = 0;
			while ( secondColumn < 4 )
			{
				newMatrix.data[firstRow][firstColumn] += this->data[firstRow][secondColumn] * rhs.data[secondColumn][firstColumn];
				secondColumn++;
			}
			firstColumn++;
		}
		firstRow++;
	}
	return std::move( newMatrix );
}

Matrix Matrix::operator*=( const Matrix& rhs )
{
	*this = *this * rhs;
	return *this;
}	

/*
Matix Matrix::scaleTranslationMatrix( Matrix transMat, const Matrix& scaleMat)
{
	transMat.data[3][0] * = scaleMat.data[0][0];
	return (transMat);
}
*/
