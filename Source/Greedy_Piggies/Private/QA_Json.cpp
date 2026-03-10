// Fill out your copyright notice in the Description page of Project Settings.


#include "QA_Json.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"

/*

QA_Json::QA_Json()
{
}

QA_Json::~QA_Json()
{
}

// 1. Define your data structure
USTRUCT(BlueprintType)
struct FMyGameData
{
    GENERATED_BODY()

    UPROPERTY()
    FString PlayerName;

    UPROPERTY()
    int32 Score;
};

// 2. Serialize and Save at Runtime
void SaveJson()
{
    FMyGameData Data;
    Data.PlayerName = "Hero";
    Data.Score = 1500;

    FString JsonString;
    // Industry standard: Convert Struct -> JSON String
    if (FJsonObjectConverter::UStructToJsonObjectString(Data, JsonString))
    {
        FString SavePath = FPaths::ProjectSavedDir() + TEXT("SaveData.json");
        FFileHelper::SaveStringToFile(JsonString, *SavePath);
    }
}
*/
