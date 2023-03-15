#include "Geometries.h"

Geometries* Geometries::instancePtr = nullptr;

Geometries::Geometries(const nlohmann::json& file)
{
    parseGeometry(file);

    instancePtr = this;
}

Geometries* Geometries::getInstance()
{
    return instancePtr;
}

void Geometries::parseGeometry(const nlohmann::json& file)
{
	for (auto itr = file["geometry"].begin(); itr != file["geometry"].end(); itr++) {
        std::string type;
        
        int i = 0;
        Eigen::Vector3f ac(0, 0, 0);
        for (auto itr2 = (*itr)["ac"].begin(); itr2 != (*itr)["ac"].end(); itr2++) {
            if (i < 3) {
                ac[i++] = (*itr2).get<float>();
            }
        }

        i = 0;
        Eigen::Vector3f dc(0, 0, 0);
        for (auto itr2 = (*itr)["dc"].begin(); itr2 != (*itr)["dc"].end(); itr2++) {
            if (i < 3) {
                dc[i++] = (*itr2).get<float>();
            }
        }

        i = 0;
        Eigen::Vector3f sc(0, 0, 0);
        for (auto itr2 = (*itr)["sc"].begin(); itr2 != (*itr)["sc"].end(); itr2++) {
            if (i < 3) {
                sc[i++] = (*itr2).get<float>();
            }
        }

        float ka = (*itr)["ka"].get<float>();
        float kd = (*itr)["kd"].get<float>();
        float ks = (*itr)["ks"].get<float>();

        float pc = (*itr)["pc"].get<float>();

		type = (*itr)["type"].get<std::string>();

        if (type == "sphere") {
            Eigen::Vector3f centre(0, 0, 0);
            i = 0;
            for (auto itr2 = (*itr)["centre"].begin(); itr2 != (*itr)["centre"].end(); itr2++) {
                if (i < 3) {
                    centre[i++] = (*itr2).get<float>();
                }
            }

            float radius = (*itr)["radius"].get<float>();

            Sphere* newGeo = new Sphere(centre, radius, ac, dc, sc, ka, kd, ks, pc);
            geometries.push_back(newGeo);
        }
        else if (type == "rectangle")
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
            
            Rectangle* newGeo = new Rectangle(v[0], v[1], v[2], v[3], ac, dc, sc, ka, kd, ks, pc);
            geometries.push_back(newGeo);
        }

	}
}

void Geometries::prettyPrint() const
{
    int len = geometries.size();
    for (int i = 0; i < len; i++)
    {
        geometries[i]->prettyPrint();
    }
}