#pragma once

#include "CoreMinimal.h"
#include "FUserHardwareData.generated.h"

USTRUCT()
struct FUserHardwareData
{
	GENERATED_BODY()

	UPROPERTY() FString CPUBrand = "Unknown";
	UPROPERTY() int32 CPUCoreCount = -1;

	UPROPERTY() FString GPUBrand = "Unknown";
	UPROPERTY() FString renderingPlatform = "Unknown";
	
	UPROPERTY() FString totalPhysicalRAM_GB = "Unknown";

	UPROPERTY() FString OSVersion = "Unknown";
};