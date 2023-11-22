#include "Map.h"
#include "TextureManager.h"

constexpr int LEVELHEIGHT = 20;
constexpr int LEVELWIDTH = 25;

int level1[LEVELHEIGHT][LEVELWIDTH] = {
	{0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0},
	{0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0},
	{4,3,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
	{5,3,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
	{0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0},
	{0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0},
	{0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0},
	{0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0},
	{0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0},
	{0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0},
	{0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0},
	{0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0},
	{0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0},
	{0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0},
	{0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0},
	{0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0},
	{0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0},
	{0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0},
	{0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0},
	{0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0},
};

Map::Map()
{
	road = TextureManager::LoadTexture("assets/environment/road.png");
	grass = TextureManager::LoadTexture("assets/environment/grass.png");
	water = TextureManager::LoadTexture("assets/environment/water.png");

	LoadMap(level1);

	src.x = src.y = 0;
	src.w = dest.w = 32;
	src.h = dest.h = 32;

	dest.x = dest.y = 0;
}

Map::~Map()
{
	SDL_DestroyTexture(road);
	SDL_DestroyTexture(water);
	SDL_DestroyTexture(grass);
}


void Map::LoadMap(int array[20][25])
{
	for (int row = 0; row < LEVELHEIGHT; row++)
	{
		for (int column = 0; column < LEVELWIDTH; column++)
		{
			map[row][column] = array[row][column];
		}
	}
}

void Map::DrawMap()
{
	int type = 0;
	
	for (int row = 0; row < LEVELHEIGHT; row++)
	{
		for (int column = 0; column < LEVELWIDTH; column++)
		{
			type = map[row][column];

			//Updates the position of the next square by 32 pixels
			dest.x = column * 32;
			dest.y = row * 32;

			switch (type)
			{
			case 0:
				TextureManager::Draw(grass, src, dest);
				break;
			case 1:
				TextureManager::Draw(water, src, dest);
				break;
			case 2:
				TextureManager::Draw(road, src, dest);
				break;
			case 3:
				TextureManager::Draw(road, src, dest, 0, SDL_FLIP_HORIZONTAL);
				break;
			case 4:
				TextureManager::Draw(road, src, dest, 90, SDL_FLIP_HORIZONTAL);
				break;
			case 5:
				TextureManager::Draw(road, src, dest, 90, SDL_FLIP_NONE);
				break;
			default:
				break;
			}
		}
	}
}



