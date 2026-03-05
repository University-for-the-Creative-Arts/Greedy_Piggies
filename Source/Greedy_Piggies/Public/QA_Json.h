#pragma once

#include "CoreMinimal.h"
#include "QA_Json.generated.h"

USTRUCT(BlueprintType)
struct FMyGameData
{
    GENERATED_BODY()

    UPROPERTY()
    FString PlayerName;

    UPROPERTY()
    int32 Score;
};

class GREEDY_PIGGIES_API QA_Json
{
public:
    QA_Json();
    ~QA_Json();

    static void SaveJson();
};