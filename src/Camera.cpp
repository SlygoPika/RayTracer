#include "Camera.h"
#define M_PI           3.14159265358979323846


Camera::Camera(nlohmann::json& file)
{
    parseCamera(file);

    lookat.normalize();
    up.normalize();
    side = up.cross(lookat);

    tanVal = (float) tan(fov * M_PI / 360.0);
    nearPlaneEdge = tanVal * nearPlane;

    deltaXPixel = 2 * tanVal * nearPlane / viewport.x;
    deltaYPixel = 2 * tanVal * nearPlane / viewport.y;
    halfDeltaXPixel = deltaXPixel / 2;
    halfDeltaYPixel = deltaYPixel / 2;

    setupRays();
}

Eigen::Vector3f Camera::emitRay(int& pixelX, int& pixelY, std::vector<Geometry*>& geometries)
{
    Ray ray = viewport.pixelRays[pixelY][pixelX];
    //ray.prettyPrint(pixelX, pixelY);

    for (auto i = geometries.begin(); i < geometries.end(); i++)
    {
        if ((*i)->intersects(ray))
        {
            return (*i)->ambiantColor;
        }
    }

    return backgroundColor;
}

void Camera::setupRays()
{
    for (int y = 0; y < viewport.y; y++)
    {
        
        std::vector<Ray> row;

        for (int x = 0; x < viewport.x; x++)
        {
            appendRay(x, y, row);
        }

        viewport.pixelRays.push_back(row);
    }
}

void Camera::appendRay(int x, int y, std::vector<Ray>& row)
{
    float upMagnifier = nearPlaneEdge - (y * deltaYPixel) - halfDeltaYPixel;
    float sideMagnifier = nearPlaneEdge - (x * deltaXPixel) - halfDeltaXPixel;

    Eigen::Vector3f direction = nearPlane * lookat + up * upMagnifier + side * sideMagnifier;
    direction.normalize();

    Ray ray(position, direction);

    row.push_back(ray);
}

void Camera::parseCamera(nlohmann::json& file)
{
    for (auto itr = file["output"].begin(); itr != file["output"].end(); itr++) {
        int i = 0;
        for (auto itr2 = (*itr)["lookat"].begin(); itr2 != (*itr)["lookat"].end(); itr2++) {
            if (i < 3) {
                lookat[i++] = (*itr2).get<float>();
            }
        }

        i = 0;
        for (auto itr2 = (*itr)["up"].begin(); itr2 != (*itr)["up"].end(); itr2++) {
            if (i < 3) {
                up[i++] = (*itr2).get<float>();
            }
        }

        i = 0;
        for (auto itr2 = (*itr)["bkc"].begin(); itr2 != (*itr)["bkc"].end(); itr2++) {
            if (i < 3) {
                backgroundColor[i++] = (*itr2).get<float>();
            }
        }

        i = 0;
        for (auto itr2 = (*itr)["centre"].begin(); itr2 != (*itr)["centre"].end(); itr2++) {
            if (i < 3) {
                position[i++] = (*itr2).get<float>();
            }
        }

        viewport.x = (*itr)["size"][0].get<int>();
        viewport.y = (*itr)["size"][1].get<int>();

        fov = (*itr)["fov"].get<float>();
    }
}

void Camera::prettyPrint()
{
    std::cout << "Camera:" << std::endl;
    std::cout << "FOV: " << fov <<std::endl;
    std::cout << "tanval: " << tanVal << std::endl;
    std::cout << "Background color (r,g,b): " << backgroundColor[0] << ", " << backgroundColor[1] << ", " << backgroundColor[2] << std::endl;
    std::cout << "Position (x,y,z): " << position[0] << ", " << position[1] << ", " << position[2] << std::endl;
    std::cout << "Viewport (x,y): " << viewport.x << ", " << viewport.y << std::endl;
    std::cout << "Lookat (x,y,z): " << lookat[0] << ", " << lookat[1] << ", " << lookat[2] << std::endl;
    std::cout << "Up (x,y,z): " << up[0] << ", " << up[1] << ", " << up[2] << "\n" << std::endl;
}