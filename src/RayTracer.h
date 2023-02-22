#ifndef RAYTRACER_CLASS_H
#define RAYTRACER_CLASS_H

#include <iostream>
#include <string>
#include <vector>

#include "../external/json.hpp"
#include "../external/simpleppm.h"

#include "Geometries.h"
#include "Camera.h"

class RayTracer
{
private:
	std::vector<double> buffer;
	std::string outputFile;

	nlohmann::json file;
	Geometries geometries;
	Camera cam;

	void outputPPM();
	void fillBuffer();

public:

	RayTracer(nlohmann::json file);

	void run();
};

#endif