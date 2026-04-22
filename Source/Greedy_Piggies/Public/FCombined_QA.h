#pragma once
#include "FSingle_QA.h"
#include "CoreMinimal.h"
#include "FCombined_QA.generated.h"


USTRUCT(BlueprintType)
struct FCombined_QA
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FSingle_QA no1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FSingle_QA no2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FSingle_QA no3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FSingle_QA no4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FSingle_QA no5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FSingle_QA no6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FSingle_QA no7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FSingle_QA no8;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FSingle_QA no9;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FSingle_QA no10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FSingle_QA no11;
};
