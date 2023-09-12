
TraderPlusCurrencyModule GetTraderPlusCurrencyModule()
{
    return TraderPlusCurrencyModule.Cast(CF_ModuleCoreManager.Get(TraderPlusCurrencyModule));
}

[CF_RegisterModule(TraderPlusCurrencyModule)]
class TraderPlusCurrencyModule: CF_ModuleWorld
{
    ref TraderPlusCurrencySettings currencySettings;

    override void OnInit()
	{
        super.OnInit();
		EnableInvokeConnect();
		EnableMissionStart();
    }

    void InitializeModule()
    {
        if(GetGame().IsServer())
        {
            currencySettings = TraderPlusCurrencySettings.Load();
        }
        else
        {
            currencySettings = new TraderPlusCurrencySettings();
        }

        InitRPCs();
    }

    void InitRPCs()
    {
        if(GetGame().IsClient())
        {
            AddLegacyRPC("GetTraderPlusCurrencyResponse", SingleplayerExecutionType.Client);
        }
    }

    void OnPlayerConnect(PlayerBase player, PlayerIdentity identity)
    {
        GetRPCManager().SendRPC(ClassName(), "GetTraderPlusCurrencyResponse", new Param1<TraderPlusCurrencySettings>(currencySettings), true, identity);
    }

    void SetCurrencySettings(TraderPlusCurrencySettings settings)
    {
        currencySettings = settings;
    }

    //----------------------------------------------------------------//
	//Currency Methods
	//----------------------------------------------------------------//

    bool CheckIfPlayerHasEnoughMoney(PlayerBase player, int amount, TStringArray acceptedCurrencyTypes = null)
    {
        int playerMoneyAmount = GetPlayerMoneyFromAllCurrency(player, acceptedCurrencyTypes);
        if(playerMoneyAmount < amount)
            return false;

        return true;
    }

    int GetPlayerMoneyFromAllCurrency(PlayerBase player, ref TStringArray acceptedCurrencyTypes = null)
    {
      GetTraderPlusCoreLogger().LogDebug("GetPlayerMoneyFromAllCurrency");
      if(!acceptedCurrencyTypes)
        acceptedCurrencyTypes = new TStringArray();

      int amount = 0;
      foreach(TraderPlusCurrencyType currencyType : currencySettings.currencyTypes)
      {
        //check if currencyName is accepted
        if(acceptedCurrencyTypes.Count() > 1 && acceptedCurrencyTypes.Find(currencyType.currencyName) == -1)
            continue;

        amount += GetPlayerMoneyFromCurrency(player,currencyType);
      }

      return amount; 
    }

    int GetPlayerMoneyFromCurrency(PlayerBase player, TraderPlusCurrencyType currencyType)
    {
       int amount = 0;

      array<EntityAI> itemsArray = TraderPlusCoreHelper.GetItemsArray(player);
      foreach(EntityAI entity: itemsArray)
      {
        ItemBase item = ItemBase.Cast(entity);
        if(!item)
            continue;

        TraderPlusCurrency currency = currencyType.GetCurrencyForClassName(item.GetType());
        if(!currency)
            continue;
        
        float quantity = TraderPlusCoreHelper.GetItemAmount(item);
        int value = currency.value;
        amount += value * quantity;
      }
    
      GetTraderPlusCoreLogger().LogDebug(string.Format("GetPlayerMoneyFromCurrency currencyType :%1 amount:%2",currencyType.currencyName, amount));
      return amount;
    }

    /**
     * Removes the specified amount of money from the player's inventory for the accepted currency types.
     *
     * @param player The player whose inventory to check and remove money from.
     * @param amountToRemove The amount of money (in the first accepted currency type) to remove from the player's inventory.
     * @param acceptedCurrencyTypes The list of accepted currency types.
     *
     * @return true if the required amount has been successfully removed.
     */
    bool RemoveMoneyAmountFromPlayer(PlayerBase player, int amountToRemove, ref TStringArray acceptedCurrencyTypes = null)
    {
        if(!acceptedCurrencyTypes)
        acceptedCurrencyTypes = new TStringArray();

        int amountRemoved = 0;
        int take = 0;
        int moneyAmountRemaining = amountToRemove;

        foreach(TraderPlusCurrencyType currencyType : currencySettings.currencyTypes)
        {
            //check if currencyName is accepted
            if(acceptedCurrencyTypes.Count() > 0 && acceptedCurrencyTypes.Find(currencyType.currencyName) == -1)
                continue;
            
            if(amountToRemove <= 0)
                continue;

            foreach(TraderPlusCurrency currency: currencyType.currencies)
            {
                int currentCurrencyQuantity = TraderPlusCoreHelper.GetTotalQuantityOfItem(player, currency.GetCurrencyClassName());
                take = 0;

                while ((moneyAmountRemaining > 0) && (take < currentCurrencyQuantity))
                {
                    take++;
                    moneyAmountRemaining -= currency.GetCurrencyValue();
                    amountRemoved += currency.GetCurrencyValue();
                }

                if (take > 0)
                {
                    bool success = TraderPlusCoreHelper.RemoveOurProduct(player, currency.GetCurrencyClassName(), take);
                    if (!success)
                        return false;
                }
            }
        }

        if (amountRemoved > amountToRemove)
  	    {
  		    int difference = amountRemoved - amountToRemove;
            AddMoneyToPlayer(player, difference, acceptedCurrencyTypes);
  	    }
        
        // Return true if the required amount has been successfully removed
        return amountToRemove <= 0;
    }

    void AddMoneyToPlayer(PlayerBase player, int amount, ref TStringArray acceptedCurrencyTypes = null)
    {
        if(!acceptedCurrencyTypes)
            acceptedCurrencyTypes = new TStringArray();

        foreach (TraderPlusCurrencyType currencyType : currencySettings.currencyTypes)
        {
            // Check if currencyName is accepted
            if (acceptedCurrencyTypes.Count() > 0 && acceptedCurrencyTypes.Find(currencyType.currencyName) == -1)
                continue;

            foreach(TraderPlusCurrency currency: currencyType.currencies)
            {
                int value = currency.GetCurrencyValue();
            
                if (value <= 0 || value > amount)
                    continue;
                
                int amountToAdd = amount / value;
                
                // Create a new instance of the currency item to add to the player's inventory
                ItemBase currencyItem = TraderPlusCoreHelper.CreateInInventory(player, currency.GetCurrencyClassName(), amountToAdd);
                
                if (!currencyItem)
                    continue;
                
                // Update the remaining amount to add
                amount -= amountToAdd * value;
                
                // Stop adding money if the desired amount has been reached
                if (amount <= 0)
                    break;
            }
        }
    }

    //----------------------------------------------------------------//
	//Events Methods
	//----------------------------------------------------------------//

    //! OnInvokeConnect is called on each connect, reconnect, and respawn
	override void OnInvokeConnect(Class sender, CF_EventArgs args)
	{
		super.OnInvokeConnect(sender, args);

		auto cArgs = CF_EventPlayerArgs.Cast(args);

		if (!IsMissionHost())
			return;

		if (!cArgs.Player || !cArgs.Identity)
			return;

		OnPlayerConnect(cArgs.Player, cArgs.Identity);
 	}

    override void OnMissionStart(Class sender, CF_EventArgs args)
	{
		super.OnMissionStart(sender, args);
        InitializeModule();
	}
    //----------------------------------------------------------------//
	//RPC Methods
	//----------------------------------------------------------------//

    void GetTraderPlusCurrencyResponse(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if(type != CallType.Client)
            return;

        Param1<TraderPlusCurrencySettings> data;
        if(!ctx.Read(data))
            return;

        currencySettings = data.param1;

        GetTraderPlusCoreLogger().LogDebug("GetTraderPlusCurrencyResponse");
    }
}
