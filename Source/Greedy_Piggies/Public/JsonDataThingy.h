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
	UFUNCTION(BlueprintCallable, Category = "HowToMakeAJson") static void JsonMakerAndSender(const FCombinedUserData combinedUserData);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HowToMakeAJson") static FUserHardwareData GetUserHardware();
private:
	void SendJson();
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
