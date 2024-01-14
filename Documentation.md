# Game Project Documentation - Jiayu Hu

## Overview

My game project is organized into a Game object, which includes a state machine, with two main states: Start State and Play State. In GameLoop.cpp, Game is initalized, updated, rendered and exited.

To run the game, open Game.sln in Visual Studio, then click on "Start without Debugging" button or press ctrl + F5.

When running the game, to control the character, player can only use direction keys (WASD and Up/Down/Left/Right) to move and Space key to jump.

### Pre-Programming Code Acknowlegement
The following system/engine blocks are pre-programmed before Jan 12, 2024 by me: 
- Tile system (Tile class and TileMap class)
- State machine class
- Entity class
- Game Level class
- Player class

## Main Game

The main game's state machine manages the overall flow of the game and transitions between the following states:

1. **Start State**: Initial state when the game is launched.
2. **Play State**: The main state where the game is actively played.

## Game Components

### Play State

The Play State consists of:
- **LevelMaker**: Make a GameLevel randomly using unique algorithms.
- **GameLevel**: Represents the game level, including map, entities and game objects.
- **Player**: Represents the character that could controlled by the player.

### Level Maker

The Level Maker's variables include:

- **Tilemap**: Represents the layout of the game world.
    - **Tile**: Represents the Tile of the Tilemap.
        - The Tile's unique ID, which is the frame number on the sprite sheet.
        - The Tile's position, dimension and sprite.
- **MapData**: A 2D vector including ID representation of the tilemap. Every ID in the vector represents a Tile.
- **NewLevel**: A new GameLevel that is generated and will be passed to the Play State.

The Level Maker's functions include:
- **GenerateData**: Generating MapData using algorithms that loop through the whole map and generate different tile's ID at the 2D vector randomly.
- **GenerateDecor**: Adding decorations (rock, grass, tree, etc) as Game Objects using algorithms that loop through the whole map and add them to different locations randomly.
- **Generate**: Based on the return values of GenerateData and GenerateDecor during runtime, generate a new Game Level and return it.

### Game Level

The Game Level's variables include:

- **Tilemap**: Represents the layout of the game world.
- **Entity**: Various living entities present in the game, including Slime and Bat. 
    - The Entity's position, dimension and sprite
    - The Entity's own StateMachine, direction, and boolean value representing it is dead or not.
- **GameObject**: Represents inanimate objects present in the game, including rock, tree, and grass, etc. 
    - The GameObject's position, dimension and sprite.

### Player Entity

The Player entity includes:

- **State Machine**: Manages different states such as Idle, Walking, Jump, Falling, Dead, Win, etc.
- **score**: Represents the score player gets from elimilating Slime or Bat.
- **isWin**: Represents if player wins the current level or not.

### Slime Entity

The Slime entity includes:

- **State Machine**: Manages states like Moving, Chasing, Dead, etc.

### Bat Entity

The Bat entity includes:

- **Bat Machine**: Manages states like Flying, Diving, Dead, etc.

## Credits

- Player's sprite:
    - https://lucky-loops.itch.io/character-satyr
- Slime's sprite:
    - https://rvros.itch.io/pixel-art-animated-slime
- Tile and envirnment sprite:
    - https://trixelized.itch.io/starstring-fields
- Sound effects:
    - https://opengameart.org/content/50-rpg-sound-effects
    - https://opengameart.org/content/jump-landing-sound
    - https://opengameart.org/content/foot-walking-step-sounds-on-stone-water-snow-wood-and-dirt
- Background music:
    - https://opengameart.org/content/enchanted-festival

