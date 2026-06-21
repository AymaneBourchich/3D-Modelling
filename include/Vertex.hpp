#pragma once

#include <glm/glm.hpp>
#include <string>
#define MAX_BONE_INFLUENCE 4

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal   = glm::vec3(0.0f);
    glm::vec2 texCoord = glm::vec2(0.0f);
    
    glm::vec3 Tangent;
    glm::vec3 Bitangent;

    int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];

};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};  