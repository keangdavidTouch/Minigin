#pragma once

namespace kd
{
	struct PlayBoundary
	{
		PlayBoundary() 
			: MinX(0), MinY(0), MaxX(0), MaxY(0){};
		PlayBoundary(float minX, float minY, float maxX, float maxY)
			: MinX(minX), MinY(minY), MaxX(maxX), MaxY(maxY){};
		float MinX, MinY;
		float MaxX, MaxY;
	};

	struct GameContext
	{
		GameContext(){};
		GameContext(int windowWidth, int windowHeight)
		{
			Col = windowWidth / int(GridSize);
			Row = windowHeight / int(GridSize);

			Boundary.MinX = 0;
			Boundary.MinY = GridSize;
			Boundary.MaxX = float(windowWidth) - GridSize;
			Boundary.MaxY = float(windowHeight) - (GridSize * 2);
		};

		int Col = 0;
		int Row  = 0; 
		float Scale  = 3.f;
		int SpriteSize = 16;
		float GridSize = SpriteSize * Scale;
		PlayBoundary Boundary = PlayBoundary();
	};
}

