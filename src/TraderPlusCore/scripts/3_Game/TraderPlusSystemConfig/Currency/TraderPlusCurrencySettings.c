/**
 * @file TraderPlusCurrencySettings.c
 *
 * @brief This is the implementation file for the TraderPlusCurrencySettings class.
 */

/**
 * @class TraderPlusCurrencySettings
 *
 * @brief The TraderPlusCurrencySettings class handles exchange rates between different currencies.
 *
 * The TraderPlusCurrencyExchange class has functionalities to add currency type,
 * convert currency and get cross rate of currencies.
 */
class TraderPlusCurrencySettings
{
    string version = TRADERPLUS_CURRENT_VERSION;
    ref array<ref TraderPlusCurrencyType> currencyTypes; /**< An array to store different currency types. */

    /**
     * Constructor - Initializes the array of currencies.
     */
    void TraderPlusCurrencySettings()
    {
        currencyTypes = new array<ref TraderPlusCurrencyType>();
    }

    /**
     * Adds a new currency type to the list of known currencies.
     *
     * @param currencyName Name of the new currency type.
     */
    void AddCurrencyType(string currencyName)
    {
        TraderPlusCurrencyType newCurrencyType = new TraderPlusCurrencyType(currencyName);
        currencyTypes.Insert(newCurrencyType);
    }

    /**
     * Gets the currency type object for a given currency name.
     *
     * @param currencyName Currency name of the currency type.
     *
     * @returns Returns the currency type object for the given currency name.
     */
    TraderPlusCurrencyType GetCurrencyType(string currencyName)
    {
        foreach (TraderPlusCurrencyType type : currencyTypes)
        {
            if (type.currencyName == currencyName)
                return type;
        }

        return null; // type not found
    }

    void DefaultCurrencySettings()
	{
        TraderPlusCurrencyType currencyType1 = new TraderPlusCurrencyType("EUR");
        currencyType1.AddCurrency("TraderPlus_Money_Euro100", 100);
        currencyType1.AddCurrency("TraderPlus_Money_Euro50", 50);
        currencyType1.AddCurrency("TraderPlus_Money_Euro10", 10);
        currencyType1.AddCurrency("TraderPlus_Money_Euro5", 5);
        currencyType1.AddCurrency("TraderPlus_Money_Euro1", 1);
        TraderPlusCurrencyType currencyType2 = new TraderPlusCurrencyType("USD");
        currencyType1.AddCurrency("TraderPlus_Money_Dollar100", 100);
        currencyType1.AddCurrency("TraderPlus_Money_Dollar50", 50);
        currencyType1.AddCurrency("TraderPlus_Money_Dollar10", 10);
        currencyType1.AddCurrency("TraderPlus_Money_Dollar5", 5);
        currencyType1.AddCurrency("TraderPlus_Money_Dollar1", 1);
        currencyTypes.Insert(currencyType1);
        currencyTypes.Insert(currencyType2);
		//some code
		Save();
	}

	void Save()
	{
		JsonFileLoader<TraderPlusCurrencySettings>.JsonSaveFile(TRADERPLUS_CURRENCY_CONFIG, this);
	}

	void CheckVersion()
	{
		if(version != TRADERPLUS_CURRENT_VERSION)
		{
			version = TRADERPLUS_CURRENT_VERSION;
			Save();
		}
	}

	void MakeDirectoriesIfNotExist()
	{
		if ( !FileExist( TRADERPLUS_CONFIG_ROOT_SERVER ) )
			MakeDirectory( TRADERPLUS_CONFIG_ROOT_SERVER );

		if ( !FileExist( TRADERPLUS_CONFIG_DIR_SERVER ) )
			MakeDirectory( TRADERPLUS_CONFIG_DIR_SERVER );
	}

    static ref TraderPlusCurrencySettings Load()	
	{
		TraderPlusCurrencySettings settings = new TraderPlusCurrencySettings();

		settings.MakeDirectoriesIfNotExist();

		if (FileExist(TRADERPLUS_CURRENCY_CONFIG)) {
			JsonFileLoader<TraderPlusCurrencySettings>.JsonLoadFile(TRADERPLUS_CURRENCY_CONFIG, settings);
			settings.CheckVersion();
			return settings;
		}
		
		settings.DefaultCurrencySettings();
		return settings;
	}
}
