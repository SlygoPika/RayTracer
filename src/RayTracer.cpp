#include "RayTracer.h"

RayTracer::RayTracer(nlohmann::json file) :file(file), cam(file), geometries(file), outputFile(file["output"][0]["filename"].get<std::string>()) {}

void RayTracer::run()
{
	std::cout << "RayTracer is running" << "\n" << std::endl;
	geometries.prettyPrint();
	cam.prettyPrint();
	fillBuffer();
	outputPPM();
}

void RayTracer::fillBuffer()
{
	int height = cam.viewport.y;
	int width = cam.viewport.x;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Eigen::Vector3f hitColor = cam.emitRay(x, y, geometries.geometries);

			buffer.push_back(hitColor[0]);
			buffer.push_back(hitColor[1]);
			buffer.push_back(hitColor[2]);
		}
		
	}
}

void RayTracer::outputPPM()
{
	save_ppm(outputFile, buffer, cam.viewport.x, cam.viewport.y);
}