/**
 * @file TraderPlusCurrency.c
 *
 * @brief This is the implementation file for the TraderPlusCurrency class.
 */

/**
 * @class TraderPlusCurrency
 *
 * @brief The TraderPlusCurrency class represents a currency with its name and value.
 *
 * The TraderPlusCurrency class has functionalities to create and manage a currency object.
 */
class TraderPlusCurrency
{
	string className; /**< Name of the currency. */
	int value; /**< Value of the currency. */

	/**
	 * Constructor - Initializes the name and value of the currency.
	 *
	 * @param className Name of the currency.
	 * @param value Value of the currency.
	 */
	void TraderPlusCurrency(string className, int value)
	{
		this.className = className;
		this.value = value;
	}

	int GetCurrencyValue()
	{
		return value;
	}

	string GetCurrencyClassName()
	{
		return className;
	}
}

