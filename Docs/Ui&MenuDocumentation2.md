# UI & Menus Documentation

## Overview
* **Class Type:** UI System / User Widget
* **Parent Class:** UserWidget / PlayerController logic
* **Description:** : This system manages the user interface flow for "Greedy Piggies," handling everything from the high-level Main Menu navigation to the complex in-game "Web" simulation (Shop and Stock markets) and input mode switching.

---

## Core Logic and Gameplay Systems
Detailed breakdown of how the class operates during runtime.

### Logic Flow
* **Initialization:** 
   *   The system triggers Set Input Mode UIOnly when menus are active to prevent world interaction.
   *  Upon entering a lobby, TotalPlayers is set based on the game mode (e.g., 2 for 1v1), and ReadyPlayers increments as each user interacts with a "Ready" button in the MainMenu.

   *    When the `BP_StockObject` constructor runs, it pushes data into variables to update the visual "Financial Web" UI.
* **Main Loop:** 
   *   The system utilizes a Current Menu State enum and the `IA_Pause` input action to toggle between gameplay and the Pause Menu. It also handles specific transitions for Multiplayer (via the 'M' key) and Character Selection.
   *   The Market Shuffle logic purges and re-populates the `AllStockArray` at the start of every round.
   *   Data Visualization: The Stock UI currently uses a data-visualization canvas to show market volatility.
* **Dependencies:** List other classes, Interfaces, or Subsystems this class requires to function.
   *   `BP_StockObject`: A constructor class used to calculate market values.
   *   `S_CardData` (Struct): Used by the Shop to define upgrade properties.
   *   Requires `BP_FirstPersonCharacter` for player data (Score/Hand) 
   *   `BP_StockObject` for market data.

---

## Variables and Data
| Variable Name | Type | Default Value | Description |
| :--- | :--- | :--- | :--- |
| **MainMenu** | WB Main Menu (Object Reference) | None / Null | Stores the active instance of the Main Menu widget to allow for direct visibility toggles or removal from parent. |
| **FoundGame?** | Boolean | False | Determines if the player should bypass the main menu on start. |
| **PauseMenu** | WB Pause (Object Reference) | None / Null | Stores the reference to the standardized Pause Overlay to manage the Set Input Mode UIOnly logic when triggered. |
| **StockName** | Text | Empty | Tracks if the player is in "Financial Tasks" or gameplay. |
| **StockDescription** | Text | Description | Immersive flavor text regarding the company's current market status. |
| **StockLogo** | Texture2D | Default_Icon | The visual branding displayed on the stock's modular UI card. |
| **StockPrice** | Float | 0.0 | The current trading value calculated using the base 100,000.0 investment ratio. |
| **Availiable** | Boolean | False | Tracks if the stock is currently active in the market pool for the current round. |
| **TotalPlayers** | Integer | 0 | Tracks the maximum number of participants (Player + AI or multiple Players) expected for the session. |
| **ReadyPlayers** | Integer | 0 | Tracks how many players have confirmed they are ready to transition from the Main Menu to the game stage. |
| **Stock Array** | Array (Stock Data) | (Populated) | The list of available stocks to be shuffled. |
| **Investment Ratio** | Float | 1.0 | Current multiplier for stock buy-ins. |



---

## Blueprint Functions and Events

### Public Functions and Events
* Generate Stocks(): Clears the current list and shuffles the AllStockArray to pick random stock entries for the round.
* Apply Menu State (PC Greedy Piggies): Updates the Player Controller's state based on the selected menu (e.g., None vs. Pause).
* UpdateScore (Card Interaction): Breaks the `S_CardData` struct to update the player's currency/hand when a shop item is purchased.

### Custom Events and Dispatchers
* `OnCardSelected_Event_0`: Triggered when a player clicks a card in the shop; it casts to the character to update Score and Hand data.
* `BuyStock`: Custom event bound to the "Invest" button; handles the transaction logic for stock purchases.
RSS Feed Animation: Triggered to loop random text headlines via the RSS Feed animation track.

---

## Interfaces and Communication
* Casting: Extensively uses Casting to `BP_FirstPersonCharacter` to sync UI selections with the player's inventory and points.
* Inter-Class Communication: * Uses Event Binding (e.g., Bind Event to On Card Selected) to allow child widgets (Shop Cards) to communicate with the parent UI container.
  * Communicates with `BP_StockObject` via the StockList to update investment ratios on hover.

---

## Integration and Setup
1. Placement: UI logic is primarily housed in the Player Controller or a dedicated HUD Class to ensure persistence across levels.
2. Configuration: Ensure the All Stock Array is populated in the Stock Website widget to prevent empty listings.
3. Usage: Press 'M' to call the Multiplayer menu or '`IA_Pause`' (Gamepad Special Right) to toggle the pause state.

--- 

## Performance and Constraints
* Tick: Not required; the system relies on Event-Driven logic and Animations (RSS Feed).
* Optimization: The "Generate Stocks" function uses a For Loop with a fixed index (0 to 3) to limit the number of active widgets and prevent frame drops during shop initialization.
* Known Issues: Ensure "Flush Input" is unchecked when setting UI mode to avoid losing initial click events on menu load.

 <br>  

![MainMenu](https://media.githubusercontent.com/media/University-for-the-Creative-Arts/Greedy_Piggies/staging/Docs/UI%20Screenshots/MainMenu.png)

*Figure 1.1: The primary landing hub featuring the Greedy Piggies branding and core play-mode selection.*

![PauseMenu](https://media.githubusercontent.com/media/University-for-the-Creative-Arts/Greedy_Piggies/staging/Docs/UI%20Screenshots/PauseMenu.png)

*Figure 1.2: Standardized Pause Overlay for real-time game state management.*

![OptionsMenu](https://media.githubusercontent.com/media/University-for-the-Creative-Arts/Greedy_Piggies/staging/Docs/UI%20Screenshots/OptionsMenu.png)

*Figure 1.3: Sub-menu architecture for Control mapping and audio/visual toggles.*

![OptionsMenu](https://media.githubusercontent.com/media/University-for-the-Creative-Arts/Greedy_Piggies/staging/Docs/UI%20Screenshots/GamepadControlsMenu.png)

*Figure 1.4: The current Gamepad remapping screen. We are binding UI buttons to the input context so the player can verify their layout on the fly.*

![PauseMenu](https://media.githubusercontent.com/media/University-for-the-Creative-Arts/Greedy_Piggies/staging/Docs/UI%20Screenshots/ShopMenuWIP.png)

*Figure 2.1: Early layout for the Shop Website, utilizing a Tab-based navigation system.*

![PauseMenu](https://media.githubusercontent.com/media/University-for-the-Creative-Arts/Greedy_Piggies/staging/Docs/UI%20Screenshots/StocksMenu.png)

*Figure 2.2: Advanced Stock UI featuring real-time "Invest" buttons and a data-visualization canvas.*

![PauseMenu](https://media.githubusercontent.com/media/University-for-the-Creative-Arts/Greedy_Piggies/staging/Docs/UI%20Screenshots/Code3.png)

*Figure 3.1: RSS Feed logic and UI Input Mode management.*

![PauseMenu](https://media.githubusercontent.com/media/University-for-the-Creative-Arts/Greedy_Piggies/staging/Docs/UI%20Screenshots/ShopCode.png)

*Figure 3.2: Card selection binding and player data synchronization.*

![PauseMenu](https://media.githubusercontent.com/media/University-for-the-Creative-Arts/Greedy_Piggies/staging/Docs/UI%20Screenshots/StocksCode.png)

*Figure 3.3: Stock generation shuffle logic and Investment Ratio calculations.*