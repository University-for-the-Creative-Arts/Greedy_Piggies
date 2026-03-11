#include "Dealer.h"
// Include your custom classes here (Replace with your actual header names)
// #include "Hand.h" 
// #include "FirstPersonCharacter_HarryTesting.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ADealer::ADealer()
{
    PrimaryActorTick.bCanEverTick = false; // Set to true if you need Tick()

    TotalTurnCount = 0;
    ActivePlayerIndex = 0;
}

// Called when the game starts or when spawned
void ADealer::BeginPlay()
{
    Super::BeginPlay();

    // Replicates the "ReceiveBeginPlay -> StartGame" chain from the Blueprint
    StartGame();
}

void ADealer::StartGame()
{
    // Trigger any blueprint-specific visual logic (optional)
    OnGameStarted();

    // Start the dealing sequence with a small delay if needed (using Timers in C++)
    FTimerHandle DealTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(DealTimerHandle, this, &ADealer::StartingDeal, 0.2f, false);
}

void ADealer::StartingDeal()
{
    // Replicating the ForLoop over Hands
    for (int32 i = 0; i < Hands.Num(); i++)
    {
        if (Hands[i])
        {
            DealCard(Hands[i]);
        }
    }

    // Transition to first turn
    Turn();
}

void ADealer::Turn()
{
    // Logic for checking the player's chosen cards 
    // (Replicating the casting logic seen in the blueprint)

    /* Example of translating your BP Cast logic:
    AFirstPersonCharacter_HarryTesting* Player = Cast<AFirstPersonCharacter_HarryTesting>(UGameplayStatics::GetPlayerCharacter(this, 0));

    if (Player)
    {
        if (Player->ChosenCards.Num() < 3)
        {
            // Replicating the "select 3 cards" Print String node
            UKismetSystemLibrary::PrintString(this, TEXT("select 3 cards"), true, true, FLinearColor::Red, 10.0f);
            return;
        }
    }
    */
}

void ADealer::AI_Turn()
{
    // Implement AI Logic
}

void ADealer::AdvanceTurn()
{
    TotalTurnCount++;
    // Advance index and reset if it exceeds player count
}

void ADealer::EndOfGame()
{
    // Win/Loss resolution
}

void ADealer::DealCard(AHand* HandRef)
{
    if (!HandRef) return;
    // Logic to spawn a card and add it to the HandRef
}

void ADealer::AddToHands(AHand* Hand)
{
    if (Hand)
    {
        Hands.Add(Hand); 
    }
}

void ADealer::RefillHand()
{
    // Logic for RefillHand
}

AHand* ADealer::GetCurrentPlayerHand()
{
    if (Hands.IsValidIndex(ActivePlayerIndex))
    {
        return Hands[ActivePlayerIndex];
    }
    return nullptr;
}

void ADealer::AuditPhase()
{
    // Trigger Audit Phase logic
}

void ADealer::AuditInput()
{
    // Validate or interact with the audit
}

void ADealer::CloseShop()
{
    if (ShopWidgetRef)
    {
        ShopWidgetRef->RemoveFromParent();
    }
}

void ADealer::ResetActiveIndex()
{
    ActivePlayerIndex = 0;
}