#pragma once
#include <list>
#include <map>
#include <mutex>
#include "Chunk.h"
#include "FastNoise.h"

typedef std::map<std::pair<int, int>, Chunk*> chunk_hash_map;

class ChunkManager
{
public:
	ChunkManager();

	//noise maps for terrain generation
	static FastNoise test_noise;
	static FastNoise mountain_placement_noise;
	static FastNoise tectonical_noise;

	//int last_chunk_x = 110, last_chunk_z = 110;

	//updates world
	void Update();
	//loads the world around given chunk coordinates
	void LoadWorld(int &starting_chunk_x, int &starting_chunk_z);
	//loads given chunk
	void LoadChunk(int chunk_x, int chunk_z);
	//mutex for the chunk map
	static std::mutex chunk_map_mutex;
	//return a copy of a current version of chunk_map
	static chunk_hash_map GetChunkMap();
	~ChunkManager();
	
	//ids of threads in program
	enum ThreadId
	{
		MAIN = 0,
		WORLD_MANAGER = 1
	};

	//mutex for queue of blocks waiting to be unloaded
	static std::mutex block_unload_queue_mutex;
	//mutex for queue of chunks waiting to be unloaded
	static std::mutex chunk_unload_queue_mutex;
	//give permission to delete removed blocks
	static void GiveThreadPermissionToUnloadBlocks(ThreadId thread);
	//give permission to delete removed chunks
	static void GiveThreadPermissionToUnloadChunks(ThreadId thread);
	//queues a block to be unloaded once it is certaint that no thread uses this block
	static void QueueBlockToUnload(SimpleBlock* block);
	//queues a chunk to be unloaded once it is certaint that no thread uses this chunk
	static void QueueChunkToUnload(Chunk* block);
private:
	//helper struct
	template <typename T>
	struct ItemQueuedToUnload
	{
		ItemQueuedToUnload<T>(T* item)
		{
			this->item = item;
			//no permission by default
			this->flags[0] = false;
			this->flags[1] = false;
		}
		T* item;
		//permission from each thread
		bool flags[2];
	};

	//list of blocks to bo be unloaded once it is certaint that no thread uses this block
	static std::list<ItemQueuedToUnload<SimpleBlock>> block_unload_queue;
	//list of chunks to bo be unloaded once it is certaint that no thread uses this block
	static std::list<ItemQueuedToUnload<Chunk>> chunk_unload_queue;
	//map of chunk pointers
	static chunk_hash_map chunk_map;
};

