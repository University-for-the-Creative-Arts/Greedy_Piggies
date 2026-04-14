#pragma once

#include "CoreMinimal.h"
#include "FSingle_QA.generated.h"

USTRUCT(BlueprintType)
struct FSingle_QA
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Question;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Answer;
};
// Category = "HowToMakeAJson"