#pragma once
#include "CoreMinimal.h"
#include "FCombined_QA.h"
#include "FUserHardwareData.h"
#include "FCombinedUserData.generated.h"


USTRUCT()
struct FCombinedUserData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere) FString fileName;
	UPROPERTY(EditAnywhere) FString timePlayed;
	
	UPROPERTY(EditAnywhere) FUserHardwareData userHardwareData;
	
	UPROPERTY(EditAnywhere) FCombined_QA combined_QA;
};
