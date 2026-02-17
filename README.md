# Dungeons & Dragons

This is a text-based game written in C. It was developed as a final project for the **Introduction to Programming** course at **Ca' Foscari University of Venice**.

The game features a complete mission system, inventory management, and even a secret cheat menu.

## Features
* **Three Main Missions**: Explore the Rotting Swamp, Haunted Mansion, and Crystal Cave.
* **Final Mission**: A strategic rock-paper-scissors style battle against the Dark Lord.
* **Shop System**: Use coins collected from enemies to buy health potions, better swords, or stronger armor.
* **Save System**: You can save your progress and load it later from a list of saved games.
* **Resting**: Restore your health in the village before heading out to a new mission.

## How to Run
The project uses a `Makefile` for easy compilation. You will need `gcc` compiler installed on your system.

1.  **Compile the game**:
    Open your terminal in the project folder and type:
    ```bash
    make build
    ```

2.  **Start the game**:
    Once compiled, run the game using:
    ```bash
    make run
    ```

3.  **Clean up**:
    To remove the compiled files, use:
    ```bash
    make clean
    ```

## Gameplay Basics
* **Fights**: When you fight enemies, the game rolls a dice to determine your damage.
* **Traps**: Some rooms have traps that can take away your life points or coins.
* **Health**: You start with 20 life points. If they reach 0, the game is over.
* **Secret**: There is a hidden cheat menu in the main screen that can be unlocked with a specific key sequence (Konami code).

## Acknowledgments
I would like to thank the teaching staff of the Introduction to Programming course at Ca' Foscari University of Venice. This project was a valuable opportunity to practice the programming concepts covered in the curriculum and apply them in a practical way.