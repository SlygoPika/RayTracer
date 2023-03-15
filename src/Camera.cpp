#include "Camera.h"
#define M_PI           3.14159265358979323846

Camera* Camera::instancePtr = nullptr;

Camera::Camera(const nlohmann::json& file)
{
    parseCamera(file);

    lookat.normalize();
    up.normalize();
    side = up.cross(lookat);

    tanVal = (float) tan(fov * M_PI / 360.0);
    nearPlaneYEdge = tanVal * NEAR_PLANE;
    nearPlaneXEdge = nearPlaneYEdge * viewport.x / viewport.y;

    deltaPixel = 2 * tanVal * NEAR_PLANE / viewport.y;
    halfDeltaPixel = deltaPixel / 2;

    setupRays();

    instancePtr = this;
}

Eigen::Vector3f Camera::emitRay(const int& pixelX, const int& pixelY) const
{
    Ray ray = viewport.pixelRays[pixelY][pixelX];

    std::vector<Geometry*>& geometries = Geometries::getInstance()->geometries;

    float minIntersect = FAR_PLANE;
    Geometry* geoToRender;

    // Test which geometry(ies) intersect with the ray
    for (auto geoItr = geometries.begin(); geoItr < geometries.end(); geoItr++)
    {
        float intersect;
        if ((*geoItr)->intersects(ray, intersect))
        {
            if (intersect < minIntersect)
            {
                minIntersect = intersect;
                geoToRender = *geoItr;
            }
        }
    }

    // If an intersect was found, fetch color of object hit
    if (minIntersect < FAR_PLANE)
    {
        Eigen::Vector3f point = minIntersect * ray.direction + ray.origin;
        Eigen::Vector3f color = geoToRender->computeLighting(point);
        clampColor(color);
        return color;
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

void Camera::appendRay(const int& x, const int& y, std::vector<Ray>& row) const
{
    float upMagnifier = nearPlaneYEdge - (y * deltaPixel) - halfDeltaPixel;
    float sideMagnifier = nearPlaneXEdge - (x * deltaPixel) - halfDeltaPixel;

    Eigen::Vector3f direction = NEAR_PLANE * lookat + up * upMagnifier + side * sideMagnifier;
    direction.normalize();

    Ray ray(position, direction);

    row.push_back(ray);
}

void Camera::clampColor(Eigen::Vector3f& color) const
{
    color[0] = std::min(color[0], 1.0f);
    color[1] = std::min(color[1], 1.0f);
    color[2] = std::min(color[2], 1.0f);
}

Camera* Camera::getInstance()
{
    return instancePtr;
}

const Viewport& Camera::getViewport() const
{
    return viewport;
}

const Eigen::Vector3f& Camera::getPosition() const
{
    return position;
}

void Camera::parseCamera(const nlohmann::json& file)
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

void Camera::prettyPrint() const
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