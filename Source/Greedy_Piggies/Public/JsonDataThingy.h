#pragma once
#include "CoreMinimal.h"
#include "FCombinedUserData.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Interfaces/IHttpRequest.h"
#include "HttpModule.h"
#include "JsonDataThingy.generated.h"

UCLASS()
class GREEDY_PIGGIES_API UJsonDataThingy : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "HowToMakeAJson") static void JsonMakerAndSender(float secondsPlayed, const FCombined_QA combined_QA);
		
protected:
	
private:
	static FUserHardwareData GetUserHardware();
	void SendJson();
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	FString static FileNameMaker();
	FString static TimePlayedFormatter(float secondsPlayed);
};
