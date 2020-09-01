/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvhParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 04:39:01 by nathan            #+#    #+#             */
/*   Updated: 2020/09/01 23:29:05 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BVHPARSER_CLASS_H
# define BVHPARSER_CLASS_H

#include <vector>
#include <string>
#include <map>
#include "Vec3.hpp"
#include <sstream>

struct bvhData {
	int numberOfFrames;
	std::vector<std::vector<Vec3>> data;
	//data[number of frame][part of body]
};

class bvhParser {
public:
	bvhParser(void);
	~bvhParser(void);
	static bvhData loadFile(std::string fileName);
private:
	static std::vector<int> const order;
	static void stringstreamToData(std::stringstream& ss, bvhData* data);
};


#endif
