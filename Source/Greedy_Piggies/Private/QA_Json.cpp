#include "QA_Json.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

QA_Json::QA_Json()
{
}

QA_Json::~QA_Json()
{
}

void QA_Json::SaveJson()
{
    FMyGameData Data;
    Data.PlayerName = "Hero";
    Data.Score = 1500;

    FString JsonString;

    if (FJsonObjectConverter::UStructToJsonObjectString(Data, JsonString))
    {
        FString SavePath = FPaths::ProjectSavedDir() + TEXT("SaveData.json");
        FFileHelper::SaveStringToFile(JsonString, *SavePath);
    }
}