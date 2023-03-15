#ifndef GEOMETRIES_CLASS_H
#define GEOMETRIES_CLASS_H

#include <iostream>
#include <string>
#include <vector>

#include "../external/json.hpp"

#include "Geometry.h"
#include "Sphere.h"
#include "Rectangle.h"

class Geometries
{
private:
	static Geometries* instancePtr;
	void parseGeometry(const nlohmann::json& file);

public:
	std::vector<Geometry*> geometries;

	Geometries(const nlohmann::json& file);

	Geometries(const Geometries& obj) = delete;

	static Geometries* getInstance();

	void prettyPrint() const;
};

#endif