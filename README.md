# **COMP3016 Console-based Game Report**

## **Table of Contents**
- [Project Overview](#project-overview)
- [Video Walkthrough](#video-walkthrough)
- [Dependencies & Resources](#dependencies-and-resources)
- [Game Programming Patterns Used](#game-programming-patterns-used)
- [Game Mechanics](#game-mechanics)
- [UML Design Diagram](#uml-design-diagram)
- [Sample Screens](#sample-screens)
- [Exception Handling and Test Cases](#exception-handling-and-test-cases)
- [Evaluation](#evaluation)

---

## **Project Overview**
This project is a **rogue-like game** that features multiple levels with increasing difficulty, providing players with a relatively challenging experience that feels progressive.

### Key Features:
- **Multiple Levels**: Players will navigate through a various levels, each with its unique layout and challenges, ensuring that gameplay remains fresh.
  
- **Increasing Difficulty**: As players progress through the game, they will encounter increasingly difficult enemies and obstacles, requiring them to adapt and develop their strategies to survive.

- **Increasing Number of Enemies**: The game introduces an increasing number of enemies that move randomly throughout the levels. This adds to the unpredictability and challenge, forcing players to stay alert.

- **Permanent Data Storage**: Player data is stored permanently in a file, allowing for seamless progress tracking. This means that players can return to the game later and pick up right where they left off, without losing their progress.

- **Sense of Progress**: The game is designed to instill a sense of progress in players, as they advance through levels and collect coins, they can obtain extra health upgrades and unlock a new map.

- **Puzzle Elements**: The game features slight puzzle mechanics, including a button that opens walls. This adds an extra layer of challenge, requiring players to think and figure out where to go before they navigate through levels.

Overall, the aim of the game was to be simple and quick yet fun, providing a satisfying sense of progression as players overcome challenges and unlock new features. This design choice ensures that players feel rewarded for their efforts without being overwhelmed and spending long time on trying to progress.

---

## **Video Walkthrough**
**[Watch the Video Walkthrough]()**

This video provides an overview of the project, including:
- Articulation of game features
- A playthrough of the game

---

## **Dependencies and Resources**
This project was developed using the following tools and libraries:

- **Coding Environment**: Visual Studio 2022
- **C++ Standard Libraries**:
  - `#include <iostream>`: For input and output stream operations.
  - `#include <fstream>`: For file handling.
  - `#include <string>`: For using string data type.
  - `#include <vector>`: For using dynamic arrays.
  - `#include <conio.h>`: For console input/output functions (like `getch()`).
  - `#include <cstdlib>`: For general purpose functions (e.g., memory allocation, random number generation).
  - `#include <ctime>`: For working with date and time functions.

- **Map Files**:
  - `map.txt`: First level of the game.
  - `map2.txt`: Second level of the game.
  - `map3.txt`: Third level of the game.
  - `map4.txt`: Fourth level of the game that the player can access after completing all the previous levels and buying it from the shop.
  - `player_data.txt`: Player's information that should be automatically generated with default values at game start.

Make sure you have the necessary environment, libraries, and resources set up before running the project.

---

## **Game Programming Patterns Used**

## 1. Game Loop Pattern
The `gameLoop` function embodies the classic game loop pattern, where the game continually processes input, updates game state, and renders the game until a termination condition (like the player losing all health) is met.

## 2. State Management
The code manages different states of the game, such as the main menu, the shop, and different levels. The `showMainMenu`, `showShopMenu`, and `transitionToNextLevel` functions serve to change states. Each function encapsulates behavior related to that specific state, making it easier to manage transitions and logic specific to each phase of the game.

## 3. Partial Entity-Component System (ECS)
The code partially follows a simplified version of ECS with a `Player` class that encapsulates attributes and behaviors (like position and health). This separation of concerns helps in managing entities and their properties cleanly. The `Player` class contains all data related to the player and methods that operate on that data.

## 4. Data-Driven Design
The game utilises external data files (`player_data.txt`, `map.txt`, etc.) to load player data and map configurations, following the data-driven design pattern. This allows me to separate game data from game logic, making it easier to modify the game without altering the source code.

## 5. Input Handling
The use of `_getch()` for input management captures player input directly from the keyboard, allowing for immediate response. The handling of input in the `showMainMenu` and `gameLoop` functions demonstrates a simple state-based input handling mechanism where different inputs trigger different game actions depending on the current state.

## 6. Singleton Pattern
The Player object is defined globally, as a single instance. This can ensure that there’s a single source for player state and behavior.

## 7. Encapsulation
The `Player` class encapsulates player-related data and functionality, allowing to manage health, position, and player interactions through methods. This encapsulation enhances code maintainability and clarity, making it easier to understand how the player behaves and interacts with the game world.

## 8. Random Movement Logic
The `moveEnemies` function implements simple AI behavior for enemies by randomly choosing directions. This randomness introduces an element of unpredictability, which can make gameplay more engaging.

## 9. Collision Detection
Functions like `isPlayerHit`, `movePlayer`, and the checks within `gameLoop` handle collision detection. These methods determine when the player interacts with enemies, collects items, or hits boundaries, forming the foundation of game mechanics related to movement and interaction.

## 10. Action Listeners/Callbacks
Functions such as `activateButton` demonstrate a form of action listeners, where specific game events (like stepping on a button) trigger corresponding actions in the game world.

## 11. Resource Management
The code manages resources (such as player health, currency, and map data) through functions that load and save to files. This allows the game state to persist between sessions, which is crucial for maintaining player progress.

---

## **Game Mechanics**


---

## **UML Design Diagram**


---

## **Sample Screens**


---

## **Exception Handling and Test Cases**

---

## **Evaluation**
