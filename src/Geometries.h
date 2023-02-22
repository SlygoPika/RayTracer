#ifndef GEOMETRIES_CLASS_H
#define GEOMETRIES_CLASS_H

#include <iostream>
#include <string>
#include <vector>

#include "../external/json.hpp"
#include "../external/simpleppm.h"

#include "Geometry.h"
#include "Sphere.h"
#include "Rectangle.h"


class Geometries
{
private:
	void parseGeometry(nlohmann::json& file);

public:
	std::vector<Geometry*> geometries;

	Geometries(nlohmann::json& file);
	void prettyPrint();
};

#endif