#include "Player.h"
#include "World/Chunk/ChunkManager.h"
#include "World/Chunk/ChunkConstants.h"
#include "World/Block/BlockData.h"
#include "GLFW/glfw3.h"
#include "Ray.h"

Player::Player(float aspect) : m_Camera(aspect, 90.0f, glm::vec3(0.0f, 60.0f, 0.0f))
{
}

const glm::vec3& Player::GetPosition() const
{
	return m_Camera.m_Position;
}

const glm::vec3& Player::GetFront() const
{
	return m_Camera.m_Front;
}

void Player::ProcessMouseInput(float xoffset, float yoffset, float dt)
{
	m_Camera.ProcessMouseInput(xoffset, yoffset, dt);
}

void Player::ProcessKeyboardInput(GLFWwindow* context, float dt)
{
	m_Camera.ProcessKeyboardInput(context, dt);
}

void Player::ProcessMouseButton(const ChunkManager& manager, GLFWwindow* context)
{
	static bool isPressed = false;
	if (glfwGetMouseButton(context, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !isPressed)
	{
		ShootRay(manager);
		isPressed = true;
	}
	else if (glfwGetMouseButton(context, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && isPressed)
	{
		isPressed = false;
	}
}

void Player::ShootRay(const ChunkManager& manager)
{
	const int Reach = 2;
	const int RangeWidth = 2 * Reach + 1;
	const int NumOfBlocksInRange = RangeWidth * RangeWidth * RangeWidth;

	const glm::vec3& PlayerPos = this->GetPosition();

	std::vector<HitRecord> BlockList;
	// Iterate through blocks in range and add pointers to them to BlockList
	for (int x = 0; x != RangeWidth; ++x)
	for (int z = 0; z != RangeWidth; ++z)
	for (int y = 0; y != RangeWidth; ++y)
	{
		HitRecord temp;
		temp.BlockPos.x = floor(PlayerPos.x + (float)x - (float)Reach);
		temp.BlockPos.y = floor(PlayerPos.y + (float)y - (float)Reach);
		temp.BlockPos.z = ceil(PlayerPos.z + (float)z - (float)Reach);

		const int ChunkX = floor(temp.BlockPos.x / CHUNK_WIDTH);
		const int ChunkZ = ceil(temp.BlockPos.z / CHUNK_WIDTH);
		temp.ChunkPtr = manager.isChunkLoaded(ChunkPosition(ChunkX, ChunkZ), manager.m_LoadedChunks);

		if (temp.ChunkPtr)
		{
			int x = static_cast<int>(temp.BlockPos.x);
			int y = static_cast<int>(temp.BlockPos.y);
			int z = static_cast<int>(temp.BlockPos.z);

			x = (x < 0) ? CHUNK_WIDTH - (x % CHUNK_WIDTH) : x % CHUNK_WIDTH;
			y = (y < 0) ? CHUNK_HEIGHT - (y % CHUNK_WIDTH) : y % CHUNK_HEIGHT;
			z = (z > 0) ? CHUNK_WIDTH - (z % CHUNK_WIDTH) : -(z % CHUNK_WIDTH);

			if (temp.ChunkPtr->m_ChunkData.GetBlockType(x, y, z) != BlockType::AIR)
			{
				temp.BlockIdx[0] = x;
				temp.BlockIdx[1] = y;
				temp.BlockIdx[2] = z;
				BlockList.push_back(temp);
			}
		}
	}

	Ray ray(PlayerPos, GetFront());
	HitRecord result = ray.TestBlockList(BlockList);

	// Get the block idx
	if (result.ChunkPtr)
	{
		result.ChunkPtr->m_ChunkData.SetBlockType(result.BlockIdx[0], result.BlockIdx[1], result.BlockIdx[2], BlockType::AIR);
		result.ChunkPtr->isSetup = false;
	}
}


