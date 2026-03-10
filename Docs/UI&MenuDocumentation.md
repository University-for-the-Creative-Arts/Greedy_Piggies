Gemini said
🐷 Greedy Piggies: UI & Systems Development Progress
This document outlines the current state of the User Interface and backend logic for Greedy Piggies. Our focus has been on creating a seamless bridge between complex economic data and player-facing interactions.

🖥️ Menu Hierarchy & UX Design
We are currently iterating on the "Web-UI" aesthetic, mimicking in-game apps for the shop and stock market.

Main & Navigation Menus
The main menu is functional, featuring a bold, high-contrast style. We are using grey-box prototyping for the Pause and Options menus to ensure the UX flow is solid before applying final assets.

Menu	Filename	Status
Main Menu	MainMenu.png	Active - Includes Online/Local & Manual
Pause Menu	PauseMenu.png	Prototype - Basic layout & sliders
Options	OptionsMenu.png	Prototype - Sub-menu navigation
In-Game "Websites"
The core gameplay revolves around two primary interfaces: the Shop for upgrades and the Stock Market for wealth accumulation.

Shop (WIP): Utilizes a dynamic three-card layout.

Stocks: Features "IPM" (International PigMachine Corp) listings and a dedicated graph area for market trends.

🛠️ Blueprint & Systems Architecture
The logic behind the scenes ensures that data remains synchronized across the UI and the Player Character.

1. Shop & Card Interaction
We’ve implemented an event-driven system to handle card selection. By breaking the S_CardData struct, we can pass price and rarity data directly to the player's score and hand variables.

2. Market Generation & Ratios
The stock market uses a Shuffle algorithm to ensure varied gameplay each round.

Dynamic List: Items are constructed as objects and injected into the ListView.

Investment Logic: We’ve established a math-heavy flow to calculate the Investment Ratio based on a 100,000.0 baseline.

3. Dynamic RSS Feed & Widget Control
To add flavor and real-time feedback, an RSS Feed system selects random headlines and plays them through a timed animation loop.

📋 Technical Summary
[!NOTE]
Performance Optimization: All UI elements are currently being moved toward a "Data-Driven" model. Using Structs allows us to balance the game's economy without diving into the Blueprint graphs for every minor tweak.

Input Mode: Handled via Set Input Mode Game And UI to ensure seamless transitions between movement and menu interaction.

State Management: Widget Switchers are utilized to toggle between the "Shop" and "Stock" tabs efficiently.

