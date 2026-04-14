# My project wide changes that could be potentially changed.

## Enabled plugins
(Can be found in GreedyPiggies.uproject)

Former: DataSerialization, FileSDK  
Current: AnalyticsBlueprintLibrary  

## DefaultGame.ini
IncludeCrashReporter=True  

## DefaultEngine.ini:
[CrashReportClient]  
bAgreeToCrashUpload=false  
bSendUnattendedBugReports=false  
CompanyName="[GreedyPiggies]"  
DataRouterUrl="[URL of your crash report server]"  
UserCommentSizeLimit=4000  
bAllowToBeContacted=true  
bSendLogFile=true  

## GameMode
In the main game mode, track the total time elapsed
