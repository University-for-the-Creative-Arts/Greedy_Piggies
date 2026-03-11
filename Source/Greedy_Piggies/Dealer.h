#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "Dealer.generated.h"

// Forward declarations to avoid circular dependencies
class AHand;
class AFirstPersonCharacter_HarryTesting;

UCLASS(Blueprintable, BlueprintType)
class GREEDY_PIGGIES_API ADealer : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ADealer();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // VARIABLES

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dealer|State")
    int32 TotalTurnCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dealer|State")
    int32 ActivePlayerIndex;

    // Array holding references to the BP_Hand actors
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dealer|Cards")
    TArray<AHand*> Hands;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dealer|UI")
    UUserWidget* ShopWidgetRef;

    // CUSTOM NODES

    UFUNCTION(BlueprintCallable, Category = "Dealer|Game Loop")
    void StartGame();

    UFUNCTION(BlueprintCallable, Category = "Dealer|Game Loop")
    void StartingDeal();

    UFUNCTION(BlueprintCallable, Category = "Dealer|Game Loop")
    void Turn();

    UFUNCTION(BlueprintCallable, Category = "Dealer|Game Loop")
    void AI_Turn();

    UFUNCTION(BlueprintCallable, Category = "Dealer|Game Loop")
    void AdvanceTurn();

    UFUNCTION(BlueprintCallable, Category = "Dealer|Game Loop")
    void EndOfGame();

    UFUNCTION(BlueprintCallable, Category = "Dealer|Cards")
    void DealCard(AHand* HandRef);

    UFUNCTION(BlueprintCallable, Category = "Dealer|Cards")
    void AddToHands(AHand* Hand);

    UFUNCTION(BlueprintCallable, Category = "Dealer|Cards")
    void RefillHand();

    UFUNCTION(BlueprintPure, Category = "Dealer|Cards")
    AHand* GetCurrentPlayerHand();

    UFUNCTION(BlueprintCallable, Category = "Dealer|Phases")
    void AuditPhase();

    UFUNCTION(BlueprintCallable, Category = "Dealer|Phases")
    void AuditInput();

    UFUNCTION(BlueprintCallable, Category = "Dealer|Phases")
    void CloseShop();

    UFUNCTION(BlueprintCallable, Category = "Dealer|State")
    void ResetActiveIndex();

    UFUNCTION(BlueprintImplementableEvent, Category = "Dealer|Events")
    void OnGameStarted();
};