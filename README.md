# C++ 2D GameEngine
Custom C++ 2D Engine built from the ground up with SDL and GLM Library.

<p align="center">
  <img src="https://static.wixstatic.com/media/139572_c1d7a22d1e5449f1b2fb66918b40e21f~mv2.gif"  width="300">
</p>

# Engine Features:

State Machine: 
- allows the gameObject to alter its behaviour by switching its internal state.
- has Enter and Exit action which allows the gameObject to make changes when entering a new state or leaving the current state (useful for changing sprite animation)
Components Pattern: 
- defining different behaviors or capabilities for gameObject
- components are decoupled and can be reused for different gameObjects
Observer Pattern:  
- Subject owns a list of pointers to each Observer watching it.
- notify the Observer with user defined Event enum 
GameObject: 
- has a Transform Component 
- use Tag to help identifying the object which is useful for collision 
- can Add/Remove Components, Child
- has Parent-Child Transformation using glm transformation matrix, transformation of the children is relative to their parent. (e.g. pump object is a child of Dig Dug)
Inputs (Command Pattern): 
- supports keyboard, controller buttons and joystick 
- allows multi-player with controllers
- use Command Pattern for executing actions when any inputs are triggered
Sprite Animation: 
- add animated sprite to GameObject easily using SpriteComponent
- SpriteComponent requires SpriteInfo which contains all the necessary variables to animate from sprite-sheet such as source rect, speed and a map of animation clips which allows to change animation easily with user defined Animation enum    
AI PathFinding:
- PathFinder is implemented using A* Algorithm with Manhattan Heuristic Function
- use AIComponent for controlling GameObject movement
Collision:
- ColliderManager keeps track of all the collider components in the scene. 
- uses Function pointer as a callback when collider is triggered.
- collision Information is passed to the function pointer which contains hit gameObject and hit direction.
Other:
- Load/Save the game levels with Binary Files
- ResourceManager for loading textures and fonts.
- SpriteSheetManager, TileRenderComponent, TextComponent, FpsComponent
