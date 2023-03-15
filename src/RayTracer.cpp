#include "RayTracer.h"

RayTracer::RayTracer(const nlohmann::json& file) 
	:file(file), cam(file), geometries(file), lights(file), outputFile(file["output"][0]["filename"].get<std::string>()) 
{}

void RayTracer::run()
{
	std::cout << "RayTracer is running" << "\n" << std::endl;
	//geometries.prettyPrint();
	//cam.prettyPrint();
	//Lights::getInstance()->prettyPrint();
	fillBuffer();
	outputPPM();
	deleteSceneData();
}


void RayTracer::fillBuffer()
{
	int height = cam.getViewport().y;
	int width = cam.getViewport().x;

	// For every pixel, emit a ray and fetch hit color
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Eigen::Vector3f hitColor = cam.emitRay(x, y);

			buffer.push_back(hitColor[0]);
			buffer.push_back(hitColor[1]);
			buffer.push_back(hitColor[2]);
		}
		
	}
}

void RayTracer::deleteSceneData()
{
	std::cout << "Deleting scene data" << std::endl;
}

void RayTracer::outputPPM() const
{
	save_ppm(outputFile, buffer, cam.getViewport().x, cam.getViewport().y);
}