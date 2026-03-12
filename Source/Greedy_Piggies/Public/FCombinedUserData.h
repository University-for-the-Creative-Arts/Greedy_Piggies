#pragma once
#include "CoreMinimal.h"
#include "FCombined_QA.h"
#include "FCombinedUserData.generated.h"


USTRUCT(BlueprintType)
struct FCombinedUserData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString fileName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString timePlayed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FCombined_QA combined_QA;
};
