class TraderPlusLoggingSettings 
{
    int logLevel = 1;
    int refreshRateInSeconds = 60;

    void MakeDirectoryIfNotExists()
    {
       if ( !FileExist( TRADERPLUS_CONFIG_ROOT_SERVER ) )
			MakeDirectory( TRADERPLUS_CONFIG_ROOT_SERVER );

	    if ( !FileExist( TRADERPLUS_LOGGER_DIR_SERVER ) )
			MakeDirectory( TRADERPLUS_LOGGER_DIR_SERVER );
    }

    void Save()
    {
        JsonFileLoader<TraderPlusLoggingSettings>.JsonSaveFile(TRADERPLUS_LOGGER_CONFIG_FILENAME, this);
    }

    static ref TraderPlusLoggingSettings Load()
    {
        TraderPlusLoggingSettings settings = new TraderPlusLoggingSettings();

        settings.MakeDirectoryIfNotExists();

        if(FileExist(TRADERPLUS_LOGGER_CONFIG_FILENAME))
        {
            JsonFileLoader<TraderPlusLoggingSettings>.JsonLoadFile(TRADERPLUS_LOGGER_CONFIG_FILENAME, settings);
            return settings;
        }

        settings.Save();
        return settings;
    }

}