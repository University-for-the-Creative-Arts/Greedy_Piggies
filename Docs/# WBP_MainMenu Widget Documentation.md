# WBP_MainMenu Widget Documentation
## Overview
- **Designer**: Michael Wintringham, 2304751
- **Class type**: Widget Blueprint
- **Parent class**: User widget 
- **Description**: The main menu widget that the player use's to navigate through the game. The first of the menu's the player see's upon opening the game.
## **Core Logic and Gameplay Systems**
This class operate during runtime by creating the widget during initialisation and setting it as the focus widget for the player. From there it functions by simply detecting the inputs to naviagte the menu before running certain custom events, toggling visibility and changing the games input mode dependant on which buttons are pressed. 

### **Logic Flow**
 - **Initialisation**: On Construct the widget first gets the players controller and sets the input mode to be UI only to avoid the player interacting with the level at all. The focused widget is also the "Online Button", meaning this is where the players cursor starts in the menu. After that all it does is set it so the mouse cursor is visible on the screen for the player to see. 
 - **Main Loop**: The primary input handling of this blueprint is through the mouse cursor with the logic being handled by "OnHovered", "OnUnhovered" and "OnClicked" events. On Hovered and Unhovered are used by the Local and Online buttons to show extra button options such as player amounts or whether to host or join a game. On Clicked fires various events depending on the button such as unparenting the menu and opening a new one when games are joined/hosted, showing or hiding the game manual or quitting the game all together.
 - **Dependencies**: Currently WBP_ShopStocks is the only other class called by this blueprint however that may change in the future
 ## **Blueprint Functions and Events** 
 ### **Public functions** 
 - Currently no public or internal functions are used within this blueprint
 ### **Custom Events and Dispatchers**
 - Currently no custom events or dispatchers are used within this blueprint
 ## **Interfaces and Communication**
 - **Implemented interfaces**: Currently this blueprint does not impliment or use and blueprint interfaces
 - **Inter-Class Communication**: Currently the only Inter-class communication this blueprint uses is constructing another widget upon a "OnClicked" event. When "On clicked (Button 4)" is called it constructs the bleuprint "WBP_Shop Stocks"
 ## **Intergration and Setup**
 - **Placement**: This actor should be implimented as the main menu being constructed as one of the first things the player has in the game.
 - **Configuration**: No configuration in the detials panel is needed.
 - **Usage**: This logic is called through constructing the widget then adding it to the viewport.
 ## **Performance and Constraints**:
 - **Tick**: Tick is not enabled for this blueprint
 - **Optimisation**: No optimisation issues are known with this blueprint
 - **Known Issues**: There are currently no known issues with this blueprint
 
