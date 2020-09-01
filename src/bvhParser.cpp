/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvhParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 12:18:16 by nathan            #+#    #+#             */
/*   Updated: 2020/09/02 00:51:22 by nathan           ###   ########.fr       */
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

void bvhParser::stringstreamToData(std::stringstream& ss, bvhData* data)
{
	std::vector<Vec3> newElem;

	for (int i = 0; i < order.back(); i+=3)
	{
		float x, y, z;
		ss >> x >> y >> z;
		if (std::find(order.begin(), order.end(), i) != order.end())
		{
			newElem.push_back(Vec3(x, y, z));
		}
	}
	data->data.push_back(newElem);
}

bvhData bvhParser::loadFile(std::string fileName)
{
	std::ifstream file;
	std::string currentLine;
	bvhData data = {0, {{{}}}};

	file.open(fileName);
	if (!file.good())
	{
		std::cerr << "Error: couldn't open file " << fileName << std::endl;
		return bvhData{-1, {{{}}}};
	}
	while (std::getline(file, currentLine))
	{
		if (currentLine == "MOTION")
			break;
	}

	std::getline(file, currentLine);
	std::stringstream frame(currentLine);
	frame >> currentLine;
	frame >> data.numberOfFrames;
	std::getline(file, currentLine);
	int i = 0;
	while (std::getline(file, currentLine) && i < data.numberOfFrames)
	{
		std::stringstream ss(currentLine);
		stringstreamToData(ss, &data);
		i++;
	}

	file.close();
	if (i != data.numberOfFrames)
		std::cerr << "Error: number of line is not the same than what found in the bvh file" << std::endl;

	return data;
}
