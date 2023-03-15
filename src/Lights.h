#ifndef LIGHTS_CLASS_H
#define LIGHTS_CLASS_H

#include <iostream>
#include <string>
#include <vector>

#include "../external/json.hpp"

#include "Light.h"
#include "PointLight.h"

class Lights
{
private:
	static Lights* instancePtr;
	void parseLights(const nlohmann::json& file);

public:
	std::vector<Light*> lights;

	Lights(const nlohmann::json& file);

	Lights(const Lights& obj) = delete;

	static Lights* getInstance();

	void prettyPrint() const;
};

#endif