#include "JsonDataThingy.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"


void UJsonDataThingy::JsonMakerAndSender(const FCombinedUserData combinedUserData)
{
	FString JsonString;
	FString savePath = combinedUserData.fileName;
	if (FJsonObjectConverter::UStructToJsonObjectString(combinedUserData, JsonString))
	{
		FFileHelper::SaveStringToFile(JsonString, *savePath);
	}
	
	FString fileLocationMsg = "File saved to: " + savePath;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Orange, fileLocationMsg);

	void SendJson();
}

void SendJson()
{
	//Send the JSON file to the server here.
}

void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	
}



//FString SavePath = FPaths::ProjectSavedDir() + TEXT("SaveData.json");

/*
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