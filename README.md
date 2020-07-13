# C++ 2D GameEngine
Custom C++ 2D Engine built from the ground up with SDL and GLM Library.

<p align="center">
  <img src="https://static.wixstatic.com/media/139572_c1d7a22d1e5449f1b2fb66918b40e21f~mv2.gif"  width="300">
</p>

# Engine Description:

State Machine: 
- the game digdug is implemented with state class pattern where 4 functions:  HandleTransition(), Update(), Enter() and Exit().

Components Pattern: 
- defining different behaviors or capabilities for gameObject
- components are decoupled and can be reused for different gameObjects

Observer Pattern:  
- In the game DigDug, I use this pattern to update its score and life.

GameObject: 
- contains Transform 
- use Tag to help identifying the object which is useful for collision 
- can Add/Remove Components, Child
- supports Parent-Child Transformation using glm transformation matrix, transformation of the children is relative to their parent. (e.g. pump object is a child of Dig Dug)

Inputs (Command Pattern): 
- supports keyboard, controller buttons and joystick 
- allows multi-player with controllers
- use Command Pattern for executing actions when any inputs are triggered

Sprite Animation: 
- SpriteComponent -> SpriteInfo -> SpriteClips

AI PathFinding:
- PathFinder is implemented using A* Algorithm with Manhattan Heuristic Function
- use AIComponent for controlling GameObject movement

Collision:
- ColliderManager keeps track of all the collider components in the scene. 
- uses Function pointer as a callback when collider is triggered.

Other:
- Load and Save game levels with Binary Files
- ResourceManager for loading textures and fonts.
- SpriteSheetManager, TileRenderComponent, TextComponent, FpsComponent
