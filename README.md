tmx-cave-gen
============

Utility to procedurally generate 2d caves and save them to a TMX file.

This utility is designed to generate maps to be used in Tiled Map Editor:
https://github.com/bjorn/tiled/wiki

The tileset image must have tiles in this order:
  FLOOR,
  
	TOP_LEFT_WALL,
	TOP_CENTER_WALL,
	TOP_RIGHT_WALL,

	MID_LEFT_WALL,
	MID_CENTER_WALL,
	MID_RIGHT_WALL,

	BOT_LEFT_WALL,
	BOT_CENTER_WALL,
	BOT_RIGHT_WALL,

	VERTICAL_WALL,
	HORIZONTAL_WALL,
	SINGULAR_WALL
	
	
