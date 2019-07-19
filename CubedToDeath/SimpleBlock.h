#pragma once
class SimpleBlock
{
public:
	unsigned char id = 255;
	unsigned char face_visible = 63;
	unsigned char flags = 255;
	unsigned char power_level = 0;
	unsigned char light_level = 0;

	enum Direction
	{
		//	z+
		NORTH = 1,
		//	z-
		SOUTH = 2,
		//	x+
		EAST = 4,
		//	x-
		WEST = 8,
		//	y+
		TOP = 16,
		//	y-
		BOTTOM = 32
	};

	enum Flag
	{
		OPAQUE = 1,
	};

	SimpleBlock(unsigned char id = 255);
	~SimpleBlock();
	float* CreateModel(float* target, int world_x, int world_y, int world_z);
	bool GetFaceVisible(Direction direction)
	{
		return ((face_visible & direction) > 0);
	}
	void SetFaceVisible(Direction direction, bool value)
	{
		if (value) face_visible |= direction; else face_visible &= ~direction;
	}
	bool GetFlag(Flag flag)
	{
		return ((flags & flag) > 0);
	}
	void SetFlag(Flag flag, bool value)
	{
		if (value) flags |= flag; else flags &= ~flag;
	}

	//static float* CreateModel(
};

namespace blk_id
{
	enum 
	{
		air_id,
		dirt_id,
		stone_id
	};
}