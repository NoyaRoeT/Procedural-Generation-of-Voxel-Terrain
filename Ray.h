#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "World/Chunk/Chunk.h"

struct HitRecord
{
	std::shared_ptr<Chunk> ChunkPtr = nullptr;
	glm::vec3 BlockPos;
	int BlockIdx[3];
	float tmin;
	float tmax;
};


class Ray
{
public:
	glm::vec3 m_Origin;
	glm::vec3 m_Direction;

	Ray(const glm::vec3& o, const glm::vec3& d);
	bool Intersect(HitRecord& record);
	HitRecord TestBlockList(const std::vector<HitRecord>& BlockList);


};

