/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvhParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 12:18:16 by nathan            #+#    #+#             */
/*   Updated: 2020/10/01 03:22:00 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvhParser.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>

std::vector<int> const bvhParser::order
{
	//order is the same than in skeleton
	// position * number of float + offset (translation)
	0 + 3, 
	5 * 6 + 3,
	10 * 6 + 3,
	11 * 6 + 3,
	34 * 6 + 3,
	35 * 6 + 3,
	57 * 6 + 3,
	58 * 6 + 3,
	62 * 6 + 3,
	63 * 6 + 3
};

bool bvhParser::stringstreamToData(std::stringstream& ss, bvhData* data, float* yOffset)
{
	std::vector<Vec3> newElem;

	float x, y, z;
	ss >> x >> y >> z;
	if (*yOffset == 1337)
	{
		*yOffset = y;
	}
	y -= *yOffset;
	data->translationData.push_back(Vec3(x, y, z) * 0.05);
	for (int i = 3; i < order.back() + 3; i+=3)
	{
		ss >> x >> y >> z;
		if (std::find(order.begin(), order.end(), i) != order.end())
		{
			newElem.push_back(Vec3(x, y, z));
		}
	}
	if (newElem.size() != order.size())
	{
		std::cerr << "Error not everything was found in parser" << std::endl;
		return (false);
	}
	data->data.push_back(newElem);
	return (true);
}

bvhData bvhParser::loadFile(std::string fileName)
{
	std::ifstream file;
	std::string currentLine;
	bvhData data;

	file.open(fileName);
	if (!file.good())
	{
		std::cerr << "Error: couldn't open file " << fileName << std::endl;
		return bvhData(-1);
	}
	while (std::getline(file, currentLine)) //ignore joint data
	{
		if (currentLine == "MOTION")
			break;
	}

	std::getline(file, currentLine);
	std::stringstream frame(currentLine);
	frame >> currentLine;
	frame >> data.numberOfFrames;
	std::getline(file, currentLine); //ignore frame speed
	int i = 0;
	float yOffset = 1337;
	while (std::getline(file, currentLine) && i < data.numberOfFrames)
	{
		std::stringstream ss(currentLine);
		if (!stringstreamToData(ss, &data, &yOffset))
			return bvhData(-1);
		i++;
	}

	file.close();
	if (i != data.numberOfFrames)
		std::cerr << "Error: number of line is not the same than what found in the bvh file" << std::endl;

	return data;
}

void bvhData::test()
{
	std::ofstream output("test.hpp");
	output << "vector<vector<vector<float>>> animations{" << std::endl << "{" << std::endl;
	for (size_t i = 0; i < data.size(); i++)
	{
		output << "{ ";
		output << translationData[i].x << ", " << translationData[i].y << ", " << translationData[i].z;
		for (size_t j = 0; j < data[i].size(); j++)
		{
			output << ", " << data[i][j].x;
			output << ", " << data[i][j].y;
			output << ", " << data[i][j].z;
		}
		output << " }," << std::endl;
	}
	output << "}," << std::endl << "};";
}
