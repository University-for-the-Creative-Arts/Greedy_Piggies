// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QA_Json.generated.h"


UCLASS()
class GREEDY_PIGGIES_API UQA_Json : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	public:
		//UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 testInt;
		UFUNCTION(BlueprintCallable, Category = "CustomJson") static void TestFunction();
};