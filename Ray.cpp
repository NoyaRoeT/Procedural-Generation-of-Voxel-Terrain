#include "Ray.h"

Ray::Ray(const glm::vec3& o, const glm::vec3& d) : m_Origin(o), m_Direction(d)
{
}

bool Ray::Intersect(HitRecord& record)
{
	const glm::vec3& min = record.BlockPos;
	glm::vec3 max(min.x + 1.0f, min.y + 1.0f, min.z - 1.0f);
	
	float tmin = (min.x - m_Origin.x) / m_Direction.x;
	float tmax = (max.x - m_Origin.x) / m_Direction.x;
	if (tmin > tmax) std::swap(tmin, tmax);

	float tymin = (min.y - m_Origin.y) / m_Direction.y;
	float tymax = (max.y - m_Origin.y) / m_Direction.y;
	if (tymin > tymax) std::swap(tymin, tymax);

	if (tmin > tymax || tymin > tmax) return false;

	if (tymin > tmin) tmin = tymin;
	if (tymax < tmax) tmax = tymax;

	float tzmin = (min.z - m_Origin.z) / m_Direction.z;
	float tzmax= (max.z - m_Origin.z) / m_Direction.z;
	if (tzmin > tzmax) std::swap(tzmin, tzmax);

	if (tmin > tzmax || tzmin > tmax) return false;
	if (tzmin > tmin) tmin = tzmin;
	if (tzmax < tmax) tmax = tzmax;

	record.tmin = tmin;
	record.tmax = tmax;
	return true;
}

HitRecord Ray::TestBlockList(const std::vector<HitRecord>& BlockList)
{
	HitRecord temp;
	HitRecord closest;
	closest.tmin = INFINITY;
	for (auto i = BlockList.begin(); i != BlockList.end(); ++i)
	{
		temp = *i;
		if (Intersect(temp))
		{
			if(temp.tmin < closest.tmin)
			closest = temp;
		}
	}
	return closest;
}