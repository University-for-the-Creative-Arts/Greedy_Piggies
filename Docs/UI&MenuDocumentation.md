# UI & Menus Dev-Log: Greedy Piggies
### UI/UX Updates & Economic Backend Progress

Progress on the Greedy Piggies interface, refining how players navigate between the game's menus and the economic systems. The goal has been moving away from "placeholder grey-box" mode and actually hooking our financial logic into the visual elements to make the transition between standard gameplay and the "Financial Web" UI feel natural and easy to read. It’s a bit of a balancing act between making it look like a cohesive game and not breaking the underlying math.

---

## 🖥️ I. The Frontend: Player Experience & Navigation

Our menu systems are designed with a hierarchical flow, ensuring the player can transition from the main stage to the granular settings without losing context.

### 1. Main Entry & Global States
We’ve structured the menu system to maintain a clear hierarchy, allowing players to move from the main screen to settings without losing their place. Main Entry & Global States: The Main Menu provides direct access to local and online modes. We have also unified the Pause and Options menus to ensure a consistent, unobtrusive overlay that doesn't distract from the game state.
- We’ve implemented a standard Set Input Mode UIOnly logic when the pause menu triggers. This ensures the player isn't accidentally clicking the world while navigating menus.
- We’re using a standard parent-child structure for the menus. The main menu is a single UserWidget
- We’ve hooked up the UI to the Enhanced Input system. As you can see in the screenshot below, we’re currently mapping user interactions to the EnhancedActionKeyMappings

![MainMenu](https://media.githubusercontent.com/media/University-for-the-Creative-Arts/Greedy_Piggies/staging/Docs/UI%20Screenshots/MainMenu.png)

*Figure 1.1: The primary landing hub featuring the Greedy Piggies branding and core play-mode selection.*

![PauseMenu](https://media.githubusercontent.com/media/University-for-the-Creative-Arts/Greedy_Piggies/staging/Docs/UI%20Screenshots/PauseMenu.png)

*Figure 1.2: Standardized Pause Overlay for real-time game state management.*

![OptionsMenu](https://media.githubusercontent.com/media/University-for-the-Creative-Arts/Greedy_Piggies/staging/Docs/UI%20Screenshots/OptionsMenu.png)

*Figure 1.3: Sub-menu architecture for Control mapping and audio/visual toggles.*

![OptionsMenu](https://media.githubusercontent.com/media/University-for-the-Creative-Arts/Greedy_Piggies/staging/Docs/UI%20Screenshots/GamepadControlsMenu.png)

*Figure 1.4: The current Gamepad remapping screen. We are binding UI buttons to the input context so the player can verify their layout on the fly.*

---

## 📈 II. The Marketplace: Shop & Stock Ecosystem

The core of Greedy Piggies revolves around two distinct "websites" within the game’s UI: the Shop and the Stock Market.

### 1. Procedural Shopfront
The Shop uses a modular card-based system. Currently, the WIP layout supports a three-card display where players can purchase upgrades or assets.

![PauseMenu](https://media.githubusercontent.com/media/University-for-the-Creative-Arts/Greedy_Piggies/staging/Docs/UI%20Screenshots/ShopMenuWIP.png)

*Figure 2.1: Early layout for the Shop Website, utilizing a Tab-based navigation system.*

### 2. The Stock Exchange (IPM)
The Stock Market is our most data-heavy UI component. It features a list of tradable entities (such as the International PigMachine Corporation) and a dedicated graph area for visualizing market volatility.

![PauseMenu](https://media.githubusercontent.com/media/University-for-the-Creative-Arts/Greedy_Piggies/staging/Docs/UI%20Screenshots/StocksMenu.png)

*Figure 2.2: Advanced Stock UI featuring real-time "Invest" buttons and a data-visualization canvas.*

---

## ⚙️ III. Technical Architecture (Blueprint Breakdown)

Behind the visuals, we have implemented a robust event-driven system to handle the complexities of a simulated economy.

### 1. Dynamic Content & RSS Feeds
To add flavor and market context, we’ve built a scrolling RSS News Feed. This system pulls random headlines and cycles them through an animated widget, keeping the player informed of "market shifts."

| Feature | Implementation | Goal |
| :--- | :--- | :--- |
| **RSS Feed** | Random Array + Animation States | Immersive flavor text & updates |
| **Input Mode** | Game and UI Toggle | Ensure mouse focus during financial tasks |
| **Stock Gen** | Shuffle + Clear List | Prevents duplicate stocks in a single round |

![PauseMenu](https://media.githubusercontent.com/media/University-for-the-Creative-Arts/Greedy_Piggies/staging/Docs/UI%20Screenshots/Code3.png)

*Figure 3.1: RSS Feed logic and UI Input Mode management.*

### 2. Financial Logic & Investment Ratios
We’ve developed a specialized math flow to handle investments. This includes a `BP_StockObject` constructor that calculates value based on a base ratio against a 100,000.0 variable.

* **Card Interaction:** When a card is clicked, the system breaks the `S_CardData` struct and updates the character's score and hand.
* **Market Shuffle:** Every round, the market is purged and re-populated with fresh entries from the `AllStockArray`.


![PauseMenu](https://media.githubusercontent.com/media/University-for-the-Creative-Arts/Greedy_Piggies/staging/Docs/UI%20Screenshots/ShopCode.png)

*Figure 3.2: Card selection binding and player data synchronization.*

![PauseMenu](https://media.githubusercontent.com/media/University-for-the-Creative-Arts/Greedy_Piggies/staging/Docs/UI%20Screenshots/StocksCode.png)

*Figure 3.3: Stock generation shuffle logic and Investment Ratio calculations.*

---

## 🚀 IV. Development Roadmap

With the core UI containers and backend data structures in place, our next sprint will focus on:

* **Polishing the Graphing Tool:** Transitioning the blue canvas in the Stock UI to a functional, real-time line graph.
* **SFX Integration:** Adding "cha-ching" cues for successful investments and purchases.
* **Visual Polish:** Replacing the grey-box placeholders in the Options menu with themed pig-vegas assets.