# **COMP3016 Console-based Game Report**

## **Table of Contents**
- [Project Overview](#project-overview)
- [Video Walkthrough](#video-walkthrough)
- [How To Run](#how-to-run)
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

## **How To Run**

1. Open the Release folder.
2. Verify that there are 4 files labeled: map.txt, map2.txt, map3.txt and map4.txt.
3. Double-click the Console Game executable (Console Game.exe).

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

![Game Loop Code](./Code%20screenshots/game_loop.PNG)

## 2. State Management
The code manages different states of the game, such as the main menu, the shop, and different levels. The `showMainMenu`, `showShopMenu`, and `transitionToNextLevel` functions serve to change states. Each function encapsulates behavior related to that specific state, making it easier to manage transitions and logic specific to each phase of the game.

![State Management Code](./Code%20screenshots/state_change.PNG)

## 3. Partial Entity-Component System (ECS)
The code partially follows a simplified version of ECS with a `Player` class that encapsulates attributes and behaviors (like position and health). This separation of concerns helps in managing entities and their properties cleanly. The `Player` class contains all data related to the player and methods that operate on that data.

## 4. Data-Driven Design
The game utilises external data files (`player_data.txt`, `map.txt`, etc.) to load player data and map configurations, following the data-driven design pattern. This allows me to separate game data from game logic, making it easier to modify the game without altering the source code.

## 5. Input Handling
The use of `_getch()` for input management captures player input directly from the keyboard, allowing for immediate response. The handling of input in the `showMainMenu` and `gameLoop` functions demonstrates a simple state-based input handling mechanism where different inputs trigger different game actions depending on the current state.

![Input Handling Code](./Code%20screenshots/input_handling.PNG)

## 6. Singleton Pattern
The Player object is defined globally, as a single instance. This can ensure that there’s a single source for player state and behavior.

## 7. Encapsulation
The `Player` class encapsulates player-related data and functionality, allowing to manage health, position, and player interactions through methods. This encapsulation enhances code maintainability and clarity, making it easier to understand how the player behaves and interacts with the game world.

![Encapsulation Code](./Code%20screenshots/encapsulation.PNG)

## 8. Random Movement Logic
The `moveEnemies` function implements simple AI behavior for enemies by randomly choosing directions. This randomness introduces an element of unpredictability, which can make gameplay more engaging.

![Random Movement Logic Code](./Code%20screenshots/random_movement_logic.PNG)

## 9. Collision Detection
Functions like `isPlayerHit`, `movePlayer`, and the checks within `gameLoop` handle collision detection. These methods determine when the player interacts with enemies, collects items, or hits boundaries, forming the foundation of game mechanics related to movement and interaction.

![Collision Detection Code](./Code%20screenshots/collision_detection.PNG)

## 10. Action Listeners/Callbacks
Functions such as `activateButton` demonstrate a form of action listeners, where specific game events (like stepping on a button) trigger corresponding actions in the game world.

![Action Listeners/Callbacks Code](./Code%20screenshots/action_listeners_callbacks.PNG)

## 11. Resource Management
The code manages resources (such as player health, currency, and map data) through functions that load and save to files. This allows the game state to persist between sessions, which is crucial for maintaining player progress.

---

## **Game Mechanics**

## 1. Player Movement
- **Mechanic**: The player can move in various directions (up, down, left right) across a map.
- **Implementation**: The `movePlayer` function handles player movement, checking for collisions and boundries.

## 2. Enemy AI
- **Mechanic**: Enemies move randomly on the game map, creating a dynamic and unpredicatable environment for the player to navigate.
- **Implementation**: The `moveEnemies` function randomly generates movement directions for enemies, adding a challenge for the player to avoid or confront.

## 3. Health Management / Damage System
- **Mechanic**: The player has a health syustem. Colliding with enemies reduces health, and once health reaches zero, the player dies and thus the game ends, sending the user back to the main menu.
- **Implementation**: Health is managed within the `Player` class, with functions like `isPlayerHit` checking if the player has collided with an enemy.

## 4. Menu Navigation
- **Mechanic**: The player can navigate between different game states (e.g., main menu, shop menu, levels) using input from the keyboard.
- **Implementation**: The `showMainMenu`, `showShopMenu`, and other state-based functions handle transitions between these game states based on player input.

## 5. Level Progression
- **Mechanic**: The player progresses through different levels, with each level having different challenges (more enemies, difficult terrain, etc.).
- **Implementation**: The `transitionToNextLevel` function transistions the player to the next map after reaching the exit.

## 6. Item Collection
- **Mechanic**: The player can collect coins on the map, which can later be used in the shop.
- **Implementation**: Collision detection is used to check when the player moves over a coin, triggering an event of adding currency.

## 7. Resource Management
- **Mechanic**: The player has resources like health and currency that can be increased or decreased during the game. Resources may persist between sessions.
- **Implementation**: Health and currency are stored in the Player class, and external files (e.g., player_data.txt) save this data, ensuring the player’s progress persists.

## 8. Shopping System
- **Mechanic**: The player can purchase upgrades in the form of extra health using in-game currency at the shop. They can also unlock a new bonus stage and progress further into the game.
- **Implementation**: The shop is implemented in the `showShopMenu` function, where players can spend currency and improve their attributes.

## 9. Event Triggers
- **Mechanic**: Buttons in the game can trigger events like unlocking areas or transporting the player to a new map. 
- **Implementation**: The `activateButton` function handles button-triggered events in the game, which unlock new areas of the map. The `transitionToNextLevel` function handles triggering a map change when the player steps on the exit tile.

---

## **UML Design Diagram**

Below is a simple sequence diagram illustrating the flow of the game:

![Game Sequence Diagram](./sequence%20diagram.png)

---

## **Sample Screens**

### 1. Main Menu
The **Main Menu** is the entry point of the game where players can start a new game, access the shop, or exit the game. Here, the player navigates between different sections.

![Main Menu Screen](./Game%20screenshots/main_menu.PNG)

### 2. Game Screen
The **Game Screen** is where the main gameplay happens. This screen displays the player's stats (like health and coins) and shows the current area. Enemies and interactable objects like buttons or coins are visible here.

![Game Screen](./Game%20screenshots/game_screen.PNG)

### 3. Shop Screen
In the **Shop Screen**, players can purchase health upgrade or a new map. This screen shows the player’s available currency and a list of purchasable items with their prices.

![Shop Screen](./Game%20screenshots/shop_screen.PNG)

### 4. Level Transition Screen
The **Level Transition Screen** is mainly just two lines of text that shows the reward for finishing the level and how to move onto the next map, this is sometimes replaced by one of the game over screens for when the player finished a level but haven't unlocked the level after that.

![Level Transition Screen](./Game%20screenshots/level_transition_screen.PNG)

### 5. Game Over Screen
When the player’s health reaches zero or another failure condition is met, the **Game Over Screen** appears. This screen shows the reason for the game over screen and how to return to the main menu.

![Game Over Screen](./Game%20screenshots/game_over_screen.PNG)
![Game Over Screen1](./Game%20screenshots/game_over_screen1.PNG)
![Game Over Screen2](./Game%20screenshots/game_over_screen2.PNG)

---

## **Exception Handling and Test Cases**

### **Exception Handling**

This game includes various exception handling mechanisms to manage player interactions, data access, and ensure smooth gameplay.

- **Input Handling**:  
  The primary exception handling in this game responds to player input. Using the `_getch()` function, the program captures a single key press (1 character) and processes it through a switch statement. This approach reduces input errors compared to taking full strings, as players only need to press one key for each action. If the input doesn’t match a valid option, the game does nothing, helping prevent unintended actions from incorrect inputs.

- **Insufficient Coins**:  
  When the player attempts to purchase an item or upgrade, the program verifies that they have enough coins (integer) to meet the price (integer). If their balance is too low, the game displays a message indicating insufficient funds and prevents the purchase. This check ensures that player resources do not drop into negative values.

- **Level Access Restriction**:  
  When the player attempts to access the final stage (Level 4), the game checks the player's progress stored in a data file. If the level is not unlocked, the game automatically redirects the player back to the main menu with an appropriate message. This helps maintain game flow and prevents access to levels the player has not yet unlocked.

- **File Loading and Missing Data Handling**:  
  The game manages missing or corrupt data files by checking the existence and readability of files when loading player data and maps. If the player data file is missing, the game generates a new file with default values, ensuring the player can continue. Similarly, if a map file is not found, an error message is displayed, informing the player of the issue without crashing the game.

- **Out-of-Bounds Movement by Player and Enemies**:
  When the player or enemy attempts to move outside the boundaries of the map, an exception is handled to prevent invalid movement. Movement logic for both the player and enemies includes boundary checks. If a move is attempted into a wall or outside map limits, the move is blocked, and the character remains in its current position. This ensures that characters do not exit the playable map area, which maintains game stability and prevents unexpected behavior or crashes due to out-of-bounds errors.

### **Test Cases**

The following test cases were conducted to verify correct functionality of the game mechanics:

- **Test 1: Invalid Key Press in Main Menu**  
  **Test Data**: Keys pressed "G", "2", "."  
  **Expected Result**: Nothing happens.  
  **Actual Result**: Nothing happens.  
  **Action Taken**: None  

- **Test 2: Confirming Selection in Menu**  
  **Test Data**: "Enter" pressed when selecting "Shop".  
  **Expected Result**: Player is sent to the shop menu.  
  **Actual Result**: Player is sent to the shop menu.  
  **Action Taken**: None  

- **Test 3: Attempt to Buy Upgrade with Insufficient Coins**  
  **Test Data**: User has coins = 20, upgrade cost = 50.  
  **Expected Result**: Message displays "Insufficient coins."  
  **Actual Result**: Message displays "Insufficient coins."  
  **Action Taken**: None  

- **Test 4: Starting the Game**  
  **Test Data**: User presses "Enter" on "Start Game".  
  **Expected Result**: Player starts on the first map.  
  **Actual Result**: Player starts on the first map.  
  **Action Taken**: None  

- **Test 5: Player Movement**  
  **Test Data**: Player presses "A", "W", "S", "D".  
  **Expected Result**: Player moves according to the key pressed.  
  **Actual Result**: Player moves according to the key pressed.  
  **Action Taken**: None  

- **Test 6: Moving Out of Bounds**  
  **Test Data**: Player presses "W" when below a boundary wall.  
  **Expected Result**: Player does not move.  
  **Actual Result**: Boundary is replaced with player symbol.  
  **Action Taken**: Added an if-statement to prevent player movement onto boundary tiles.  

- **Test 7: Coin Collection**  
  **Test Data**: Player moves over "C" tile.  
  **Expected Result**: "C" tile is replaced with player symbol, and coins increase.  
  **Actual Result**: Same as expected.  
  **Action Taken**: None  

- **Test 8: Advancing to the Next Level**  
  **Test Data**: Player moves over "X" exit tile.  
  **Expected Result**: Player transitions to the next level and receives a reward.  
  **Actual Result**: Player transitions to the next level and receives 20 coins (intended).  
  **Action Taken**: None  

- **Test 9: Taking Damage from Enemy**  
  **Test Data**: Player walks into "E" enemy tile.  
  **Expected Result**: Player takes damage and is sent back to respawn.  
  **Actual Result**: Player moves over the "E" tile without taking damage.  
  **Action Taken**: Added logic to check for "E" tile before moving, sending the player back to "S" spawn point when damage is taken.  

- **Test 10: Game Over upon Losing All Health**  
  **Test Data**: Player takes damage when health = 1.  
  **Expected Result**: Game over message displays, and player is sent to the main menu.  
  **Actual Result**: Same as expected.  
  **Action Taken**: None  

- **Test 11: Transition to Level When Not Unlocked**  
  **Test Data**: Player tries going to level 4 without having it unlocked.  
  **Expected Result**: Player is sent back to the main menu with a message indicating the level is locked.  
  **Actual Result**: Player transitions to level 4 despite it being locked.  
  **Action Taken**: Added logic to check a value stored in the file to determine if the player has access to the next level. If not, the player is sent back to the main menu.  

- **Test 12: Game Over upon Completing Last Level**  
  **Test Data**: Player completes the last level.  
  **Expected Result**: Game over message displays, and player is presented with an option to quit.  
  **Actual Result**: Same as expected.  
  **Action Taken**: None 

---

## **Evaluation**

Overall, I believe the game was somewhat successful in showcasing a diverse range of techniques within the Object-Oriented Programming (OOP) paradigm. While the game itself is not overly complex, it provides dynamic gameplay that allows users to jump in and play without navigating through multiple menus. This streamlined experience enhances user engagement and enjoyment.

One aspect I am particularly pleased with is the clean user interface. By capturing single user inputs for navigation rather than requiring full string responses, the game reduces the likelihood of user errors and improves accessibility. Additionally, the implementation of saving user data to a file is a strong feature, allowing players to close the game and resume from the same point during their next session.

However, there are several areas I would consider improving if I were to develop the game again. One major point is the need for additional content, as the current gameplay can feel relatively fast-paced and somewhat easy to complete. Moreover, the limited options for spending coins can render coin collection less meaningful, potentially diminishing player motivation to gather them.

In conclusion, while the game may lack extensive content, it offers a fast-paced and enjoyable experience for players during their initial runs. It effectively demonstrates a variety of OOP techniques and incorporates several key game mechanics commonly found in many games, making it a valuable learning experience and a fun project overall.
