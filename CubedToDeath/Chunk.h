#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include "SimpleBlock.h"
#include <mutex>

class Chunk
{
private:
	std::vector<Vertex> vertices_simple;
	std::vector<Vertex> vertices_complex;
	//float* vertices_simple = nullptr;
	//float* vertices_complex = nullptr;
	float* vertices_fluid = nullptr;
	std::mutex vertices_mutex;
public:
	std::mutex blocks_mutex;
	int triangles_count[3];
	SimpleBlock* blocks[128][16][16];
	int height_values[16][16];
	float moisture_values[17][17];
	Chunk* north_chunk = nullptr, * south_chunk = nullptr, * west_chunk = nullptr, * east_chunk = nullptr;
	unsigned int vbo[3];
	unsigned int vao[3];
	int chunk_x, chunk_z;
	bool buffers_initialized = false;
	bool vbos_update_needed = false;
	bool vbo_complex_update_needed = false;
	bool recalculate_vbos_needed = true;
	//bool recalculate_complex_vbo_needed = false;
	bool structures_generated = false;
	bool save_needed = false;
	void InitializeBuffers();
	void GenerateTerrain();
	void GenerateStructures();
	SimpleBlock* GetBlockInArea(int& local_x, int& local_y, int& local_z, Chunk*& chunk);
	SimpleBlock* GetBlockInArea(int local_x, int local_y, int local_z);
	SimpleBlock* GetBlockInArea(glm::ivec3 local_position);
	Chunk(int chunk_x, int chunk_y);
	~Chunk();
	//void CountVisibleTriangles();
	void RecalculateVbos();
	void RecalculateComplexVbo();
	void UpdateVbos();
	void UpdateVboComplex();
	void DrawSimple();
	void DrawComplex();
	void DrawFluids();
	void FindNeighbours();
	void InitializeComplexBlocks();
	bool InView();
	static int sea_level;
	void ReplaceBlock(int block_x, int block_y, int block_z, SimpleBlock* block, bool world_coordinates = true);
	enum Type
	{
		SIMPLE = 0,
		COMPLEX = 1,
		FLUID = 2,
	};
	bool contains_redstone = false;
	bool complex_model_changed = false;
	int complex_block_count = 0;
};

