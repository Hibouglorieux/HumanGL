/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvhParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 04:39:01 by nathan            #+#    #+#             */
/*   Updated: 2020/10/01 03:22:14 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BVHPARSER_CLASS_H
# define BVHPARSER_CLASS_H

#include <vector>
#include <string>
#include <map>
#include "Vec3.hpp"
#include <sstream>

//Only loads rotation on members for now
struct bvhData {
	bvhData(void) {numberOfFrames = 0;}
	bvhData(int i) {numberOfFrames = i;}
	void test();
	int numberOfFrames;
	std::vector<std::vector<Vec3>> data;
	std::vector<Vec3> translationData;
	//data[number of frame][part of body]
};

class bvhParser {
public:
	bvhParser(void);
	~bvhParser(void);
	static bvhData loadFile(std::string fileName);
private:
	static std::vector<int> const order;
	static bool stringstreamToData(std::stringstream& ss, bvhData* data, float* yOffset);
};

#endif
