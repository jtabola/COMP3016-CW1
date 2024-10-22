#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <cstdlib>
#include <ctime>

//Player data
int currency = 0;
int maxHealth = 3;
int startX = 0, startY = 0;
int mapLevelUnlocked = 1;
int wasLevel4Purchased = 0;

//Variable to keep gameMap vector
std::vector<std::string> gameMap;

//Variable to keep track of the current map
std::string currentMap = "map.txt";

//Variable pair to keep enemies
std::vector<std::pair<int, int>> enemies;

//Function declarations
void loadPlayerData();
void savePlayerData();
void welcomeScreen();
void loadMap(const std::string& mapFile);
void transitionToNextLevel();
void gameLoop();
void displayLivesAndCoins();
void showMainMenu();
void showShopMenu();
void movePlayer(char direction);
void moveEnemies();
bool isPlayerHit();
void damagePlayer();
void activateButton();

class Player {
private:
    int playerHealth;
    int x, y;
public:
    //Constructor
    Player(int startX, int startY, int startHealth)
        : x(startX), y(startY), playerHealth(startHealth){}

    //Getters and Setters
    int getHealth() const { return playerHealth; }
    int getX() const { return x; }
    int getY() const { return y; }

    void setPosition(int newX, int newY) {
        x = newX;
        y = newY;
    }

    void takeDamage(int damage) {
        playerHealth -= damage;
    }

    void heal(int amount) {
        playerHealth += amount;
    }

    void setHealth(int amount) {
        playerHealth = amount;
    }

    //Display player status (used for testing)
    void displayStatus() const {
        std::cout << "Player Health: " << playerHealth << "\n";
        std::cout << "Player Position: (" << x << ", " << y << ")\n";
    }
};

//Default global player variable
Player player(0, 0, 0);

int main()
{
    srand(time(0));
    //Load currency and health from file 
    //Show the welcome screen
    loadPlayerData();
    welcomeScreen();
    return 0;
}

//Welcome screen function
void welcomeScreen() {
    showMainMenu();
}

//Function to display the main menu and handle user input for selection
void showMainMenu() {
    const std::string options[] = { "Start Game", "Shop", "Exit" };
    int numOptions = 3;
    int selectedOption = 0;
    char input;

    while (true) {
        //Clear screen (will only work on Windows)
        system("cls");

        //Display the menu options
        std::cout << "Welcome to the game!" << std::endl;
        std::cout << "Press either W/Up Arrow or S/Down Arrow to select and ENTER to confirm." << std::endl;
        for (int i = 0; i < numOptions; ++i) {
            if (i == selectedOption) {
                std::cout << "> " << options[i] << std::endl;
            }
            else {
                std::cout << "  " << options[i] << std::endl;
            }
        }

        //Capture user input
        input = _getch();

        //Handle input (W/S or Arrow Up/Down)
        if (input == 'w' || input == 'W' || input == 72) {
            selectedOption = (selectedOption - 1 + numOptions) % numOptions;
        }
        else if (input == 's' || input == 'S' || input == 80) {
            selectedOption = (selectedOption + 1) % numOptions;
        }
        else if (input == '\r') {
            //Execute the selected option
            switch (selectedOption) {
            case 0:
                system("cls");
                player.setHealth(maxHealth);
                savePlayerData();
                loadMap("map.txt");
                gameLoop();
                return;
            case 1:
                showShopMenu();
                break;
            case 2:
                std::cout << "Exiting game. Goodbye!" << std::endl;
                exit(0);
            }
        }
    }
}

//Shop function with menu-based navigation for upgrades
void showShopMenu() {
    const std::string upgrades[] = {
        "Increase Health (+1) - 50 coins",
        "Level 4 Map - 100 coins",
        "Exit Shop"
    };
    int numUpgrades = 3;
    int selectedUpgrade = 0;
    char input;

    while (true) {
        //Clear screen (only works on Windows)
        system("cls");

        //Display the shop options
        std::cout << "Welcome to the shop! You have " << currency << " coins." << std::endl;
        for (int i = 0; i < numUpgrades; ++i) {
            if (i == selectedUpgrade) {
                std::cout << "> " << upgrades[i] << std::endl;
            }
            else {
                std::cout << "  " << upgrades[i] << std::endl;
            }
        }

        //Capture user input
        input = _getch();

        //Handle input (W/S or Arrow Up/Down)
        if (input == 'w' || input == 'W' || input == 72) {
            selectedUpgrade = (selectedUpgrade - 1 + numUpgrades) % numUpgrades;
        }
        else if (input == 's' || input == 'S' || input == 80) {
            selectedUpgrade = (selectedUpgrade + 1) % numUpgrades;
        }
        else if (input == '\r') {
            //Execute the selected upgrade
            switch (selectedUpgrade) {
            case 0:
                if (currency >= 50) {
                    currency -= 50;
                    maxHealth += 1;
                    std::cout << "Health increased! You now have " << maxHealth << " health." << std::endl;
                    std::cout << "Remaining coins: " << currency << std::endl;
                    savePlayerData();
                    _getch();
                }
                else {
                    std::cout << "Not enough coins!" << std::endl;
                    _getch();
                }
                break;
            case 1:
                if (mapLevelUnlocked < 4) {
                    std::cout << "You must beat level 3 to unlock this." << std::endl;
                    _getch();
                    break;
                }
                else {
                    if (wasLevel4Purchased == 1) {
                        std::cout << "You've already purchased this." << std::endl;
                        _getch();
                        break;
                    }
                    else {
                        if (currency >= 100) {
                            currency -= 100;
                            std::cout << "You have unlocked the last map level." << std::endl;
                            std::cout << "Remaining coins: " << currency << std::endl;
                            wasLevel4Purchased = 1;
                            savePlayerData();
                            _getch();
                        }
                        else {
                            std::cout << "Not enough coins!" << std::endl;
                            _getch();
                        }
                    }
                }
                break;
            case 2:
                return;
            }
        }
    }
}

//Display lives and coins at the start of the game
void displayLivesAndCoins() {
    std::cout << "Coins: " << currency << std::endl;

    //Display each life as "<3"
    std::cout << "Lives: ";
    for (int i = 0; i < player.getHealth(); ++i) {
        //Print one heart for each life
        std::cout << "<3 ";
    }
    std::cout << std::endl;
}

//Load player data from file
void loadPlayerData() {
    std::ifstream file("player_data.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.find("currency") != std::string::npos) {
                currency = std::stoi(line.substr(line.find(":") + 2));
            }
            else if (line.find("health") != std::string::npos) {
                int health = std::stoi(line.substr(line.find(":") + 2));
                player.setHealth(health);
            }
            else if (line.find("mapLevelUnlocked") != std::string::npos) {
                mapLevelUnlocked = std::stoi(line.substr(line.find(":") + 2));
            }
            else if (line.find("wasLevel4Purchased") != std::string::npos) {
                wasLevel4Purchased = std::stoi(line.substr(line.find(":") + 2));
            }
        }
        file.close();
    }
    else {
        std::cout << "Player data file not found. Creating a new one with default values." << std::endl;

        //Set default values for currency and health
        currency = 100;
        maxHealth = 3;

        //Re-use the save function to create the file with default data
        savePlayerData();
    }
}

//Save player data back to file
void savePlayerData() {
    std::ofstream file("player_data.txt");
    if (file.is_open()) {
        file << "currency: " << currency << std::endl;
        file << "health: " << maxHealth << std::endl;
        file << "mapLevelUnlocked: " << mapLevelUnlocked << std::endl;
        file << "wasLevel4Purchased: " << wasLevel4Purchased << std::endl;
        file.close();
    }
}

//Load the map from a file
void loadMap(const std::string& mapFile) {
    std::ifstream file(mapFile);
    if (file.is_open()) {
        std::string line;
        gameMap.clear();
        enemies.clear();
        int y = 0;
        bool startFound = false;

        while (std::getline(file, line)) {
            gameMap.push_back(line);

            //Search for the starting position 'S'
            if (!startFound) {
                size_t pos = line.find('S');
                if (pos != std::string::npos) {
                    int playerX = pos;
                    int playerY = y;
                    player.setPosition(playerX, playerY);
                    startX = playerX;
                    startY = playerY;
                    gameMap[y][playerX] = 'O';
                    startFound = true;
                }
            }
            //Search for enemy positions marked as 'E'
            size_t enemyPos = line.find('E');
            while (enemyPos != std::string::npos) {
                //Store enemy positions
                enemies.push_back({ enemyPos, y });
                //Find more enemies
                enemyPos = line.find('E', enemyPos + 1);
            }
            y++;
        }
        if (!startFound) {
            std::cout << "Error: No starting point ('S') found in the map!" << std::endl;
        }
        file.close();
    }
    else {
        std::cout << "Map file not found!" << std::endl;
    }
}

//Game logic
void gameLoop() {
    char input;
    bool exitGame = false;

    while (!exitGame) {
        //Clear screen to update the map
        system("cls");

        //Display the map
        for (const auto& line : gameMap) {
            std::cout << line << std::endl;
        }
        //Display lives and coins
        displayLivesAndCoins();

        //Capture player input for movement
        input = _getch();

        //Move player based on input (W, A, S, D or arrow keys)
        if (input == 'w' || input == 'W' || input == 72) {
            movePlayer('U');
        }
        else if (input == 's' || input == 'S' || input == 80) {
            movePlayer('D');
        }
        else if (input == 'a' || input == 'A' || input == 75) {
            movePlayer('L');
        }
        else if (input == 'd' || input == 'D' || input == 77) {
            movePlayer('R');
        }

        //Move enemies randomly after the player moves
        moveEnemies();

        //Check if player is caught by an enemy
        if (isPlayerHit()) {
            damagePlayer();
            if (player.getHealth() <= 0) {
                std::cout << "Game Over! You've been defeated!" << std::endl;
                exitGame = true;
            }
        }
    }

    //Return to main menu after game ends
    showMainMenu();
}
//Move player function
void movePlayer(char direction) {
    int newX = player.getX(), newY = player.getY();

    //Calculate new position based on direction
    switch (direction) {
        case 'U': newY--; break;  // Up
        case 'D': newY++; break;  // Down
        case 'L': newX--; break;  // Left
        case 'R': newX++; break;  // Right
    }

    //Check if the new position is walkable (not a wall '#')
    if (gameMap[newY][newX] != '#' && gameMap[newY][newX] != '1') {
        //Check if the new position is occupied by an enemy ('E')
        for (const auto& enemy : enemies) {
            if (enemy.first == newX && enemy.second == newY) {
                damagePlayer();
                return;
            }
        }
        //Check if the player is about to step on the exit ('X')
        //Reward the player and transition to the next level
        if (gameMap[newY][newX] == 'X') {
            currency += 20;
            savePlayerData();
            std::cout << "Level complete! +20 coins!" << std::endl;
            std::cout << "Press any button to continue." << std::endl;
            _getch();
            transitionToNextLevel();
            return;
        }
        //Check if the player moves onto a coin 'C'
        if (gameMap[newY][newX] == 'C') {
            currency += 10;  // Collect coin, increase currency
        }

        //Check if the player steps on the button ('B') and call method "activateButton"
        if (gameMap[newY][newX] == 'B') {
            activateButton();
        }

        //Update map: Set current position to empty space
        gameMap[player.getY()][player.getX()] = ' ';

        //Update player position
        player.setPosition(newX, newY);

        //Set new player position to 'O'
        gameMap[player.getY()][player.getX()] = 'O';
    }
}

//Function to move enemies randomly
void moveEnemies() {
    for (auto& enemy : enemies) {
        int newX = enemy.first;
        int newY = enemy.second;

        //Choose a random direction for the enemy (0 = up, 1 = down, 2 = left, 3 = right)
        int direction = rand() % 4;

        switch (direction) {
        case 0: newY--; break;
        case 1: newY++; break;
        case 2: newX--; break;
        case 3: newX++; break;
        }

        //Check if the new position is within the map and not a wall ('#') or exit ('X')
        if (gameMap[newY][newX] != '#' && gameMap[newY][newX] != 'X' && gameMap[newY][newX] != 'C') {
            //Update map: Set current enemy position to empty space
            gameMap[enemy.second][enemy.first] = ' ';

            //Update enemy position
            enemy.first = newX;
            enemy.second = newY;

            //Set new enemy position to 'E'
            gameMap[newY][newX] = 'E';
        }
    }
}

//Check if player is caught by an enemy
bool isPlayerHit() {
    for (const auto& enemy : enemies) {
        if (player.getX() == enemy.first && player.getY() == enemy.second) {
            return true;
        }
    }
    return false;
}

//Function to handle player taking damage
void damagePlayer() {
    player.takeDamage(1);
    std::cout << "You've been hit! Health: " << player.getHealth() << std::endl;
    if (player.getHealth() > 0) {
        std::cout << "Press any button to respawn." << std::endl;
    }
    //Teleport player back to the starting position
    gameMap[player.getY()][player.getX()] = ' ';
    player.setPosition(startX, startY);
    gameMap[player.getY()][player.getX()] = 'O';
    _getch();
    //Check if player health is zero
    if (player.getHealth() <= 0) {
        std::cout << "Game Over! You've run out of health." << std::endl;
        std::cout << "Press any button to go to Menu." << std::endl;
        currentMap = "map.txt";
        _getch();
        loadPlayerData();
        showMainMenu();
    }
}
//Function to transition player depending on the current map
void transitionToNextLevel() {
    std::cout << "Loading next level..." << std::endl;

    if (currentMap == "map.txt") {
        mapLevelUnlocked = 2;
        currentMap = "map2.txt";
        loadMap("map2.txt");
    }
    else if(currentMap == "map2.txt") {
        mapLevelUnlocked = 3;
        currentMap = "map3.txt";
        loadMap("map3.txt");
    }
    else if (currentMap == "map3.txt") {
        mapLevelUnlocked = 4;
        if (wasLevel4Purchased == 1) {
            std::cout << "Good Job! Teleporting to the BOSS Stage." << std::endl;
            _getch();
            currentMap = "map4.txt";
            loadMap("map4.txt");
        }
        else {
            std::cout << "You have completed the base game! You can now buy the Final BOSS Level in the shop!" << std::endl;
            std::cout << "Press any button to go the to Menu." << std::endl;
            currentMap = "map.txt";
            _getch();
            savePlayerData();
            showMainMenu();
        }
    }
    else if (currentMap == "map4.txt") {
        system("cls");
        std::cout << "GAME OVER!" << std::endl;
        std::cout << "Thank you for beating my game!" << std::endl;
        std::cout << "Final Stats" << std::endl;
        std::cout << "Max Health: " << maxHealth << std::endl;
        std::cout << "Coins: " << currency << std::endl;
        std::cout << "Press any button to QUIT" << std::endl;
        _getch();
        savePlayerData();
        exit(0);
    }
    //Restart the game loop for the new level
    gameLoop();
}

//Function to handle the event when the player steps on the button
void activateButton() {
    std::cout << "Button activated! Unlocking paths..." << std::endl;

    //Loop through the entire map and replace all '1' tiles with empty spaces ' '
    for (size_t y = 0; y < gameMap.size(); ++y) {
        for (size_t x = 0; x < gameMap[y].size(); ++x) {
            if (gameMap[y][x] == '1') {
                gameMap[y][x] = ' ';
            }
        }
    }
}