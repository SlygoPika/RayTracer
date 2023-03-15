#ifndef RAYTRACER_CLASS_H
#define RAYTRACER_CLASS_H

#include <iostream>
#include <string>
#include <vector>

#include "../external/json.hpp"
#include "../external/simpleppm.h"

#include "Geometries.h"
#include "Lights.h"
#include "Camera.h"

class RayTracer
{
private:
	std::vector<double> buffer;
	std::string outputFile;

	nlohmann::json file;

	// Scene data
	Geometries geometries;
	Lights lights;
	Camera cam;

	void outputPPM() const;
	void fillBuffer();
	void deleteSceneData();

public:

	RayTracer(const nlohmann::json& file);

	void run();
};

#endif