#include "Lights.h"

Lights* Lights::instancePtr = nullptr;

Lights::Lights(const nlohmann::json& file)
{
    parseLights(file);

    instancePtr = this;
}

Lights* Lights::getInstance()
{
    return instancePtr;
}

void Lights::parseLights(const nlohmann::json& file)
{
	for (auto itr = file["light"].begin(); itr != file["light"].end(); itr++)
	{
        int i = 0;
        Eigen::Vector3f id(0, 0, 0);
        for (auto itr2 = (*itr)["id"].begin(); itr2 != (*itr)["id"].end(); itr2++) {
            if (i < 3) {
                id[i++] = (*itr2).get<float>();
            }
        }

        i = 0;
        Eigen::Vector3f is(0, 0, 0);
        for (auto itr2 = (*itr)["is"].begin(); itr2 != (*itr)["is"].end(); itr2++) {
            if (i < 3) {
                is[i++] = (*itr2).get<float>();
            }
        }

        std::string type = (*itr)["type"].get<std::string>();

        if (type == "point")
        {
            i = 0;
            Eigen::Vector3f centre(0, 0, 0);
            for (auto itr2 = (*itr)["centre"].begin(); itr2 != (*itr)["centre"].end(); itr2++) {
                if (i < 3) {
                    centre[i++] = (*itr2).get<float>();
                }
            }

            PointLight* newLight = new PointLight(centre, id, is);
            lights.push_back(newLight);
        }
        else if (type == "area")
        {
            std::vector<Eigen::Vector3f> v;

            for (int j = 0; j < 4; j++)
            {
                Eigen::Vector3f point(0, 0, 0);
                i = 0;
                for (auto itr2 = (*itr)["p" + std::to_string(j + 1)].begin(); itr2 != (*itr)["p" + std::to_string(j + 1)].end(); itr2++)
                {
                    if (i < 3) {
                        point[i++] = (*itr2).get<float>();
                    }
                }
                v.push_back(point);
            }

            // NEED TO IMPLEMENT AREALIGHT CLASS
        }
	}
}

void Lights::prettyPrint() const
{
    int len = lights.size();
    for (int i = 0; i < len; i++)
    {
        lights[i]->prettyPrint();
    }
}