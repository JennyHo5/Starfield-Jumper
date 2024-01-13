# Game Project Documentation

## Overview

My game project is organized into a state machine, with two main states: Start State and Play State. The Play State includes the Player entity and the Game Level. Each entity, including the Player, Slime, and Eagle, has its own state machine.

### Pre-Programming Code Acknowlegement
The following system/engine blocks are pre-programmed before Jan 12, 2024 by me: 
- The game's state machine
- Tile system (Tile class and TileMap class)
- Entity class
- Game Level class
- Level Maker class
- Player class


## Main Game

The main game state machine manages the overall flow of the game and transitions between the following states:

1. **Start State**: Initial state when the game is launched.
2. **Play State**: The main state where the game is actively played.

## Game Components

### Game Level

The Game Level consists of:

- **Tilemap**: Represents the layout of the game world.
- **Entities**: Various entities present in the game, including the Player, Slime, and Eagle.

### Player Entity

The Player entity includes:

- **State Machine**: Manages different states such as Idle, Walking, Jumping, etc.
- **Controls**: Input handling for player movement and actions.

### Slime Entity

The Slime entity includes:

- **State Machine**: Manages states like Patrolling, Chasing, Attacking, etc.
- **AI Logic**: Determines the behavior of Slime in response to the player's actions.

### Eagle Entity

The Eagle entity includes:

- **State Machine**: Manages states like Flying, Diving, Resting, etc.
- **Flight Dynamics**: Handling the movement and behavior of the Eagle in the game world.

## Credits

Player's sprite:

- https://lucky-loops.itch.io/character-satyr

Slime's sprite:

- https://rvros.itch.io/pixel-art-animated-slime

Tile and envirnment sprite:

- https://trixelized.itch.io/starstring-fields

Sound effects:

- https://opengameart.org/content/50-rpg-sound-effects

Background music:

- https://opengameart.org/content/platformer-game-music-pack

