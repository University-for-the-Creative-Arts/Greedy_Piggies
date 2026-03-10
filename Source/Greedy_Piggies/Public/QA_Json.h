// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


class GREEDY_PIGGIES_API QA_Json
{
public:
	QA_Json();
	~QA_Json();

	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 testInt;

	UFUNCTION(BlueprintCallable, Category = "CustomJson") void TestFunction();
};
