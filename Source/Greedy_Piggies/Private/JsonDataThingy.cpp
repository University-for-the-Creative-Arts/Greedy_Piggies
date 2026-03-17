#include "JsonDataThingy.h"

//#include <cmath>
//#include <string>
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "HAL/PlatformMemory.h"
#include "RHI.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

FString JsonString;

void UJsonDataThingy::JsonMakerAndSender(float secondsPlayed, FCombined_QA combined_QA)
{
	FCombinedUserData combinedUserData;
	
	FString fileName = FileNameMaker();

	//set struct variables
	combinedUserData.fileName = fileName;
	combinedUserData.timePlayed = TimePlayedFormatter(secondsPlayed);
	combinedUserData.userHardwareData = GetUserHardware();
	combinedUserData.combined_QA = combined_QA;
	
	FString savePath = FPaths::ProjectContentDir() + fileName;
	if (FJsonObjectConverter::UStructToJsonObjectString(combinedUserData, JsonString))
	{
		FFileHelper::SaveStringToFile(JsonString, *savePath);
	}
	
	FString fileLocationMsg = "File saved to: " + savePath;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Orange, fileLocationMsg);

	//void SendJson();
}

FUserHardwareData UJsonDataThingy::GetUserHardware()
{
	FUserHardwareData userHardwareData;
	
	userHardwareData.CPUBrand = FPlatformMisc::GetCPUBrand();
	userHardwareData.CPUCoreCount = FPlatformMisc::NumberOfCores();
	
	if (GDynamicRHI)
	{
		userHardwareData.GPUBrand = GRHIAdapterName;
		userHardwareData.renderingPlatform = LegacyShaderPlatformToShaderFormat(GMaxRHIShaderPlatform).ToString();
	}
	
	FPlatformMemoryStats memoryStats = FPlatformMemory::GetStats();
	float RAM = static_cast<float>(memoryStats.TotalPhysical) / (1024.0f * 1024.0f * 1024.0f);
	userHardwareData.totalPhysicalRAM_GB = FString::Printf(TEXT("%.0f"), RAM);
	
	FString OSName;
	FString OSVersion;
	FPlatformMisc::GetOSVersions(OSName,OSVersion);
	userHardwareData.OSVersion = OSName + " " + OSVersion;
	
	return userHardwareData;
}

void UJsonDataThingy::SendJson()
{
	//Send the JSON file to the server here.
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL("https://your-api-endpoint.com/data");
	Request->SetVerb("POST");

	Request->SetHeader("Content-Type", TEXT("application/json"));

	Request->SetContentAsString(JsonString);

	Request->OnProcessRequestComplete().BindUObject(this,&UJsonDataThingy::OnResponseReceived);

	Request->ProcessRequest();
}

void UJsonDataThingy::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("Response: %s"), *Response->GetContentAsString());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HTTP Request failed."))
	}
}

FString UJsonDataThingy::FileNameMaker()
{
	FDateTime now = FDateTime::UtcNow();

	FString fileName = FString::Printf(TEXT("%d-%02d-%02d_%02d-%02d-%02d_playerdata.json"),
	now.GetYear(),
	now.GetMonth(),
	now.GetDay(),
	now.GetHour(),
	now.GetMinute(),
	now.GetSecond()
	);
	
	return fileName;
}

FString UJsonDataThingy::TimePlayedFormatter(float secondsPlayed)
{
	int32 hours = FMath::TruncToInt(secondsPlayed / 3600.0f);
	float minutesRemaining = (secondsPlayed / 3600.0f - (float)hours) * 60.0f;
	int32 minutes = FMath::TruncToInt(minutesRemaining);
	float secondsRemaining = (minutesRemaining - (float)minutes) * 60.0f;
	int32 seconds = FMath::TruncToInt(secondsRemaining);
	
	return FString::Printf(TEXT("%dh %02dm %02ds"), hours, minutes, seconds);
}
