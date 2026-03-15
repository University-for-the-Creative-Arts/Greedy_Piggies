#pragma once

#include "CoreMinimal.h"
#include "FUserHardwareData.generated.h"

USTRUCT(BlueprintType)
struct FUserHardwareData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly) FString CPUBrand = "Unknown";
	UPROPERTY(BlueprintReadOnly) int32 CPUCoreCount = -1;

	UPROPERTY(BlueprintReadOnly) FString GPUBrand = "Unknown";
	UPROPERTY(BlueprintReadOnly) FString renderingPlatform = "Unknown";
	
	UPROPERTY(BlueprintReadOnly) float totalPhysicalRAM_GB = -1.0f;

	UPROPERTY(BlueprintReadOnly) FString OSVersion = "Unknown";
};