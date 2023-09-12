
static ref TraderPlusCoreLoggingModule GetTraderPlusCoreLogger()
{
    TraderPlusCoreLoggingModule module = TraderPlusCoreLoggingModule.Cast(CF_ModuleCoreManager.Get(TraderPlusCoreLoggingModule));
    
    return module;
}

[CF_RegisterModule(TraderPlusCoreLoggingModule)]
class TraderPlusCoreLoggingModule: CF_ModuleGame
{
    FileHandle fileHandle;
    int networkSync_LogLevel;
    ref TraderPlusCoreLoggingSettings settings;

    float dtime = 0;

    override void OnInit()
	{
		super.OnInit();
		RegisterNetSyncVariable("networkSync_LogLevel");
        EnableUpdate();
        EnableMissionStart();
	}

    override void OnMissionStart(Class sender, CF_EventArgs args)
	{
		super.OnMissionStart(sender, args);
		
        fileHandle = CreateNewLogFile();
        
        if(GetGame().IsServer())
        {
            settings = TraderPlusCoreLoggingSettings.Load();

            networkSync_LogLevel = settings.logLevel;
            SetSynchDirty();
        }
	}

    override void OnUpdate(Class sender, CF_EventArgs args)
	{
		auto update = CF_EventUpdateArgs.Cast(args);

		dtime += update.DeltaTime;

		if (GetGame().IsServer() && settings && dtime > settings.refreshRateInSeconds)
		{
            dtime = 0;
            settings = TraderPlusCoreLoggingSettings.Load();

            networkSync_LogLevel = settings.logLevel;
            SetSynchDirty();
		}
	}

    void MakeDirectoryIfNotExists()
    {
        //we check if config folders exist, if not we create them
        if ( !FileExist( TPG_LOGGER_ROOT_SERVER ) )
			MakeDirectory( TPG_LOGGER_ROOT_SERVER );

		if ( !FileExist( TPG_LOGGER_LOG_DIR_SERVER ) )
			MakeDirectory( TPG_LOGGER_LOG_DIR_SERVER );
    }

    FileHandle CreateNewLogFile()	
	{
        MakeDirectoryIfNotExists();

		string filePath = string.Format(TPG_LOGGER_FILENAME_SERVER, GenerateFullTimeStamp());
		//Check the file does not already exist ... fuck knows how it would
        Print(filePath);
        fileHandle = OpenFile(filePath, FileMode.WRITE);

		//File created
		if (fileHandle != 0)
		{
			FPrintln(fileHandle, "Creation Time: " + GenerateFullTimeStamp());
			return fileHandle;
		}
		return NULL;
	}

	void Log(string content, TraderPlusGarageLogLevel logLevel) 
	{
        if(logLevel >= networkSync_LogLevel)
        {
            string timeStamp = GenerateShortTimeString();
            FPrintln(fileHandle, timeStamp + " | " + GetLogLevelString(logLevel) + " | " + content);
        }
	}

	void LogError(string content) 
	{
		thread Log(content, TraderPlusGarageLogLevel.Error);
	}

	void LogInfo(string content) 
	{
		thread Log(content, TraderPlusGarageLogLevel.Info);
	}
	
	void LogDebug(string content) 
	{
		thread Log(content, TraderPlusGarageLogLevel.Debug);
	}

	void LogWarning(string content) 
	{
		thread Log(content, TraderPlusGarageLogLevel.Warning);
	}

	string GenerateShortDateString() 
	{
		int year, month, day;
		GetYearMonthDay(year, month, day);
		string ret = "" + year + "_" + month + "_" + day;
		return ret;
	}

	string GenerateShortTimeString() 
	{
		int hour, minute, second;
		GetHourMinuteSecond(hour, minute, second);
		string ret = "" + hour + "-" + minute + "-" + second;
		return ret;
	}

	string GenerateFullTimeStamp() 
	{
		string dateStr = GenerateShortDateString();
		string timeStr = GenerateShortTimeString();
		string ret = "" + dateStr + "-" + timeStr;
		return ret;
	}

	string GetLogLevelString(TraderPlusGarageLogLevel logLevel)
	{
		switch (logLevel)
		{
			case TraderPlusGarageLogLevel.Info:
				return "[INFO]";
			case TraderPlusGarageLogLevel.Error:
				return "[ERROR]";
			case TraderPlusGarageLogLevel.Debug:
				return "[DEBUG]";
            case TraderPlusGarageLogLevel.Warning:
				return "[WARNING]";
			default:
				return "";
		}

        return "";
	}
}