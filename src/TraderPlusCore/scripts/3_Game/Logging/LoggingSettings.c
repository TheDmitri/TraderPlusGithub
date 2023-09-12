class TraderPlusCoreLoggingSettings
{
	int logLevel = 0;
	int refreshRateInSeconds = 60;

	void Save()
	{
		JsonFileLoader<TraderPlusCoreLoggingSettings>.JsonSaveFile(TPG_LOGGER_CONFIG_FILE_SERVER, this);
	}

	void MakeDirectoryIfNotExists()
	{
		//we check if config folders exist, if not we create them
		if ( !FileExist( TPG_LOGGER_ROOT_SERVER ) )
			MakeDirectory( TPG_LOGGER_ROOT_SERVER );

		if ( !FileExist( TPG_LOGGER_LOG_DIR_SERVER ) )
				MakeDirectory( TPG_LOGGER_LOG_DIR_SERVER );
	}

	static ref TraderPlusCoreLoggingSettings Load()	
	{
		TraderPlusCoreLoggingSettings settings = new TraderPlusCoreLoggingSettings();

		settings.MakeDirectoryIfNotExists();

		//Now we check if config exist, if yes, we load it. if no, we call function defaultVaultHeistSettings that will initialize default value
		if (FileExist(TPG_LOGGER_CONFIG_FILE_SERVER)) 
		{
			JsonFileLoader<TraderPlusCoreLoggingSettings>.JsonLoadFile(TPG_LOGGER_CONFIG_FILE_SERVER, settings);
			return settings;
		}
	
	    settings.Save();
		return settings;
	}
};

