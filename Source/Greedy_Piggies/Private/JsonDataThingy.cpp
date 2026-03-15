#include "JsonDataThingy.h"

#include <cmath>

#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "HAL/PlatformMemory.h"
#include "RHI.h"

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
	userHardwareData.totalPhysicalRAM_GB = std::floor(RAM * 10) / 10.0f;
	
	//userHardwareData.OSName = FPlatformMisc::GetOSVersion();
	//userHardwareData.OSVersion = FPlatformMisc::GetOSVersion();
	
	FPlatformMisc::GetOSVersions(userHardwareData.OSVersion, userHardwareData.OSVersion);
	
	return userHardwareData;
}

void SendJson()
{
	//Send the JSON file to the server here.
}

void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	
}
