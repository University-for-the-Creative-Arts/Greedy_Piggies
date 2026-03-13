# Card Game System Documentation

This document outlines the core system classes derived from the project's `.COPY` files. It follows the provided documentation template structure for each major component.

---

# BP_Dealer Documentation

## Overview
* **Class Type:** Actor (Blueprint)
* **Parent Class:** Actor
* **Description:** The central manager for the game session. It handles the deck, dealing cards, managing turn order (Player vs AI), auditing gameplay (truth/bluff checks), and determining the winner.

---

## Core Logic and Gameplay Systems

### Logic Flow
* **Initialization:**
    *   **StartGame:** Initializes the game state, likely shuffling the deck and resetting scores.
    *   **StartingDeal:** Distributes the initial set of cards to all `BP_Hand` actors (Player and AI).
* **Main Loop:**
    *   **Turn:** Manages the active player's phase.
    *   **AI_Turn:** Executes logic for the AI opponent to select and play cards.
    *   **AuditPhase:** Triggered when a player challenges the previous move. Evaluates `Truth` and assigns penalties.
    *   **EndOfGame:** Checks for win conditions (e.g., empty hand) and declares the winner.
* **Dependencies:**
    *   **BP_Hand:** Stores card data for each player.
    *   **BP_AIPlayer:** The opponent actor.
    *   **BP_FirstPersonCharacter_HarryTesting:** The player character.
    *   **DT_Deck (DataTable):** Source of all card definitions.
    *   **S_Cards (Struct):** Data structure for card properties.

---

## Variables and Data

| Variable Name | Type | Default Value | Description |
| :--- | :--- | :--- | :--- |
| **fullDeck** | DataTable | DT_Deck | The master list of all cards in the game. |
| **hands** | BP_Hand Array | Empty | References to the player and AI hand containers. |
| **currentPlayer** | Integer | 0 | Index of the player currently taking their turn. |
| **player** | BP_Character | None | Reference to the local player character. |
| **AI_Player** | BP_AIPlayer | None | Reference to the AI opponent. |
| **CardPoolRow** | Int Array | Empty | Tracks available cards (likely row indices from DT_Deck). |
| **auditing** | Boolean | False | State flag indicating if an audit is in progress. |
| **Truth** | Boolean | False | Tracks if the last play was truthful or a bluff. |
| **declaredScore** | Integer | 0 | The value the player claims to have played. |
| **realScore** | Integer | 0 | The actual value of the cards played. |

---

## Blueprint Functions and Events

### Public Functions and Events
*   **StartGame**: Begins the session setup.
*   **Dealing Logic**:
    *   **StartingDeal**: Initial distribution of cards.
    *   **DealCard**: Moves a card from the pool to a target hand.
    *   **RefillHand**: Replenishes a player's hand if empty/low.
*   **Turn Management**:
    *   **Turn**: Logic for the current player's turn start.
    *   **AI_Turn**: Logic for the AI's decision making.
    *   **EndOfGame**: Clean up and win announcements.
*   **Audit System**:
    *   **AuditPhase**: Evaluates the validity of the last play.
    *   **AuditInput**: Input handler for triggering an audit.

---

## Integration and Setup
1.  **Placement:** Place one instance of `BP_Dealer` in the level.
2.  **Configuration:** Ensure `fullDeck` is set to `DT_Deck`.
3.  **Usage:** The `BP_FirstPersonCharacter` must store a reference to this actor to call playing functions.

---

# BP_FirstPersonCharacter_HarryTesting Documentation

## Overview
*   **Class Type:** Character
*   **Description:** The playable character. Manages player input, playing cards from the hand, and interacting with the UI/Dealer.

---

## Core Logic and Gameplay Systems

### Logic Flow
*   **Input Handling:**
    *   Standard movement (Jump, Look, Move).
    *   **Card Interaction:** Logic to select cards (`ChangeSelectedCard`), play them (`PlayCards`), and declare values (`UpdateScore`).
*   **Dependencies:**
    *   **BP_Dealer:** To submit turns and audits.
    *   **BP_Hand:** To view and retrieve owned cards.
    *   **BP_CardBase:** To spawn visual representations of cards (`cardActors`).

---

## Variables and Data

| Variable Name | Type | Description |
| :--- | :--- | :--- |
| **Dealer** | BP_Dealer | Reference to the main game manager. |
| **hand** | BP_Hand | Reference to this player's hand data. |
| **selectedCard** | Integer | Index of the currently highlighted card in the UI/Hand. |
| **chosenCards** | Int Array | List of cards selected to be played in the current turn. |
| **score** | Integer | The card value the player receives/tracks. |
| **cardActors** | BP_CardBase Array | 3D actors representing the cards in hand. |

---

## Blueprint Functions and Events

### Custom Events
*   **PlayCards**: Submits the `chosenCards` to the Dealer.
*   **UpdateScore**: Updates local score display/tracking.
*   **updateCards**: Refreshes the visual hand display (spawning/destroying `cardActors`).
*   **ChangeSelectedCard**: Cycles through cards in the hand.
*   **Input Actions**: `IA_Move`, `IA_Jump`, `IA_Look`, `IA_MouseLook`.

---

# BP_Hand Documentation

## Overview
*   **Class Type:** Actor / Object
*   **Description:** A data container for a player's hand. It stores the list of cards held by a participant (Player or AI).

---

## Variables and Data

| Variable Name | Type | Description |
| :--- | :--- | :--- |
| **hand** | Int Array | List of card IDs (or values) currently held. |
| **score** | Integer | Current score associated with this hand. |

---

## Blueprint Functions
*   **AddToHand**: Adds a card ID to the `hand` array.
*   **RemoveFromHand**: Removes a specific card ID from the array.

---

# Data Structures

## S_Cards (Struct)
Defines the properties of a single card.
*   **CardNumber (String):** Display name (e.g., "Ace", "Two").
*   **CardSuit (String):** Suit (e.g., "Hearts", "Spades").
*   **cardValue (Int):** Numerical value for gameplay logic.

## DT_Deck (DataTable)
*   **Row Structure:** `S_Cards`
*   **Description:** Static database defining the standard deck of cards used by `BP_Dealer` to populate the game.
