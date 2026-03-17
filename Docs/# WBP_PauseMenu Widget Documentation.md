# WBP_PauseMenu Widget Documentation
## Overview
- **Designer**: Michael Wintringham, 2304751
- **Class type**: Widget Blueprint
- **Parent class**: User widget 
- **Description**: The pause menu widget that the player use's to navigate through the game when paused during gameplay.
## **Core Logic and Gameplay Systems**
This class operate during runtime by creating the widget during initialisation and setting it as the focus widget for the player. From there it functions by simply detecting the inputs to naviagte the menu before toggling visibility and changing the games input mode dependant on which buttons are pressed. 

### **Logic Flow**
 - **Initialisation**: On Construct the widget first gets the players controller and sets the input mode to be UI only to avoid the player interacting with the level at all. The focused widget is also selected, meaning this is where the players cursor starts in the menu. After that all it does is set it so the mouse cursor is visible on the screen for the player to see. 
 - **Main Loop**: The primary input handling of this blueprint is through the mouse cursor with the logic being handled by "OnClicked" events. On Clicked fires various events depending on the button such as unparenting the menu and resuming the game, showing or hiding the game manual or quitting the game all together.
 - **Dependencies**: Currently there are no other blueprint dependencies within this blueprint.
 ## **Blueprint Functions and Events** 
 ### **Public functions** 
 - Currently no public or internal functions are used within this blueprint
 ### **Custom Events and Dispatchers**
 - Currently no custom events or dispatchers are used within this blueprint
 ## **Interfaces and Communication**
 - **Implemented interfaces**: Currently this blueprint does not impliment or use and blueprint interfaces
 - **Inter-Class Communication**: Currently there is no Inter-Class communication within this bleuprint.
 ## **Intergration and Setup**
 - **Placement**: This actor should be implimented as the menu being constructed whenever the player pauses the game whilst gameplay is active.
 - **Configuration**: No configuration in the detials panel is needed.
 - **Usage**: This logic is called through constructing the widget then adding it to the viewport.
 ## **Performance and Constraints**:
 - **Tick**: Tick is not enabled for this blueprint
 - **Optimisation**: No optimisation issues are known with this blueprint
 - **Known Issues**: There are currently no known issues with this blueprint
 
