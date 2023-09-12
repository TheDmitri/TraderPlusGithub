/**
 * @file TraderPlusCurrencyType.c
 *
 * @brief This is the implementation file for the TraderPlusCurrencyType class.
 */

/**
 * @class TraderPlusCurrencyType
 *
 * @brief The TraderPlusCurrencyType class represents a type of currency with its name and exchange rate.
 *
 * The TraderPlusCurrencyType class has functionalities to create and manage a currency type object, as well as adding and removing currencies from it.
 */
class TraderPlusCurrencyType
{
    string currencyName; /**< Name of the currency type. */
    ref array<ref TraderPlusCurrency> currencies; /**< Array of currency objects belonging to this currency type. */

    /**
     * Constructor - Initializes the name, exchange rate and an empty array of currencies of this type.
     *
     * @param currencyName Name of the currency type.
     * @param exchangeRate Exchange rate of the currency type.
     */
    void TraderPlusCurrencyType(string currencyName)
    {
        this.currencyName = currencyName;
        currencies = new array<ref TraderPlusCurrency>();
    }

    /**
     * Adds a currency object to the array of currencies of this type.
     *
     * @param className Name of the currency.
     * @param value Value of the currency.
     */
    void AddCurrency(string className, int value)
    {
        TraderPlusCurrency newCurrency = new TraderPlusCurrency(className, value);
        currencies.Insert(newCurrency);
    }

    /**
     * Sorts the currencies array from highest currency value to lowest.
     */
    void SortCurrenciesByValue()
    {
        for (int i = 0; i < currencies.Count() - 1; i++)
        {
            for (int j = i + 1; j < currencies.Count(); j++)
            {
                if (currencies[i].value < currencies[j].value)
                {
                    TraderPlusCurrency temp = currencies[i];
                    currencies[i] = currencies[j];
                    currencies[j] = temp;
                }
            }
        }
    }

    TraderPlusCurrency GetCurrencyForClassName(string className)
    {
        foreach(TraderPlusCurrency currency : currencies)
        {
            if(CF_String.EqualsIgnoreCase(currency.className, className))
                return currency;
        }

        return null;
    }

}