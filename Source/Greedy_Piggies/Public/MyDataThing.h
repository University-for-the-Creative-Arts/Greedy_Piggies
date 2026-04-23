#pragma once
#include "CoreMinimal.h"
#include "FCombinedUserData.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Interfaces/IHttpRequest.h"
#include "HttpModule.h"
#include "MyDataThing.generated.h"

UCLASS()
class GREEDY_PIGGIES_API UMyDataThing : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "MyDataFileMakers") static void JsonMakerAndSender(float secondsPlayed, const FCombined_QA combined_QA);
	UFUNCTION(BlueprintCallable, Category = "MyDataFileMakers") static void CSV_MakerAndSender(float secondsPlayed, const FCombined_QA combined_QA);
protected:
	
private:
	static FUserHardwareData GetUserHardware();
	void SendJson();
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	FString static FileNameMaker();
	FString static TimePlayedFormatter(float secondsPlayed);
};