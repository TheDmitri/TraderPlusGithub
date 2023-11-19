
static ref TraderPlusLoggerModule GetTraderPlusLogger()
{
    return TraderPlusLoggerModule.Cast(CF_ModuleCoreManager.Get(TraderPlusLoggerModule));
}

[CF_RegisterModule(TraderPlusLoggerModule)]
class TraderPlusLoggerModule : CF_ModuleGame
{
    private int networkSync_LogLevel;

    ref TraderPlusLoggingSettings settings;

    FileHandle fileHandle;

    float dtime = 0;

    float dtimeTemp = 0;


    override void OnInit()
    {
        super.OnInit();
        
        EnableUpdate();
        EnableMissionStart();
    }

    override void OnMissionStart(Class sender, CF_EventArgs args)
    {
        super.OnMissionStart(sender, args);

        fileHandle = CreateNewLogFile();

        if(GetGame().IsServer())
        {
            settings = TraderPlusLoggingSettings.Load();

            networkSync_LogLevel = settings.logLevel;
            SynchLogLevel();       
        }
        else
        {
            AddLegacyRPC("GetLogLevelResponse", SingleplayerExecutionType.Client);
        }
    }

    void GetLogLevelResponse(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		 if (type != CallType.Client)
			 return;

		 Param1<int> data;
		 if (!ctx.Read(data))
            return;

		 networkSync_LogLevel = data.param1;
	}

    void SynchLogLevel()
    {
        GetRPCManager().SendRPC(ClassName(), "GetLogLevelResponse",  new Param1<int>(networkSync_LogLevel), true, NULL);
    }

    override void OnUpdate(Class sender, CF_EventArgs args)
    {
        auto update = CF_EventUpdateArgs.Cast(args);

        dtime += update.DeltaTime;
        dtimeTemp += update.DeltaTime;

        if(GetGame().IsServer() && settings && dtime >= settings.refreshRateInSeconds)
        {
            dtime = 0;

            settings = TraderPlusLoggingSettings.Load();

            networkSync_LogLevel = settings.logLevel;
            SynchLogLevel();
        }
    }


    void MakeDirectoryIfNotExists()
    {
       if ( !FileExist( TRADERPLUS_CONFIG_ROOT_SERVER ) )
			MakeDirectory( TRADERPLUS_CONFIG_ROOT_SERVER );


		if ( !FileExist( TRADERPLUS_LOGGER_DIR_SERVER ) )
			MakeDirectory( TRADERPLUS_LOGGER_DIR_SERVER );
    }
    
    string GenerateShortDateString()
    {
        int year, month, day;
        GetYearMonthDay(year, month, day);
        return "" + year + "_" + month + "_" + day;
    }

    string GenerateShortTimeString()
    {
        int hour, minute, second;
        GetHourMinuteSecond(hour, minute, second);
        return "" + hour + "_" + minute + "_" + second;
    }

    string GenerateFullTimestamp()
    {
        string dateStr = GenerateShortDateString();
        string timeStr = GenerateShortTimeString();

        return dateStr + "-" + timeStr;
    }

    FileHandle CreateNewLogFile()
    {
        MakeDirectoryIfNotExists();

        string filePath = string.Format(TRADERPLUS_LOGGER_FILENAME, GenerateFullTimestamp());

        fileHandle = OpenFile(filePath, FileMode.WRITE);

        if(fileHandle != 0)
        {
            FPrintln(fileHandle, "Creation Time: " + GenerateFullTimestamp());
            return fileHandle;
        }

        return null;
    }

    void Log(string content, TraderPlusLogLevel logLevel)
    {
        if(logLevel < networkSync_LogLevel)
            return;
        
        string timestamp = GenerateShortTimeString();
        FPrintln(fileHandle, timestamp + " | " + GetLogLevelString(logLevel) + " | " + content);
    }

    void LogInfo(string content)
    {
        Log(content, TraderPlusLogLevel.Info);
    }

    void LogWarning(string content)
    {
        Log(content, TraderPlusLogLevel.Warn);
    }

    void LogError(string content)
    {
        Log(content, TraderPlusLogLevel.Error);
    }

    void LogDebug(string content)
    {
        Log(content, TraderPlusLogLevel.Debug);
    }

    string GetLogLevelString(TraderPlusLogLevel logLevel)
    {
        switch(logLevel)
        {
             case TraderPlusLogLevel.Debug:
                return "DEBUG";
            case TraderPlusLogLevel.Info:
                return "INFO";
            case TraderPlusLogLevel.Warn:
                return "WARNING";
            case TraderPlusLogLevel.Error:
                return "ERROR";
            default:
                return "";
        }

        return "";
    }

}