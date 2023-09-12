
[CF_RegisterModule(TraderPlusCurrencyModuleTest)]
class TraderPlusCurrencyModuleTest: CF_ModuleWorld
{
    override void OnInit()
	{
        super.OnInit();
        EnableMissionStart();
    }

    //----------------------------------------------------------------//
	//UnitTest Methods
	//----------------------------------------------------------------//

    void StartUnitTest()
    {
        Object obj = GetGame().CreateObject("SurvivorM_Jose", vector.Zero, false, false);
        PlayerBase player = PlayerBase.Cast(obj);

        player.GetInventory().CreateInInventory("NBCHoodGray");
        player.GetInventory().CreateInInventory("TacticalShirt_Grey");
        player.GetInventory().CreateInInventory("HighCapacityVest_Black");
        player.GetInventory().CreateInInventory("HunterPants_Winter");
        player.GetInventory().CreateInInventory("AthleticShoes_Blue");
        player.GetInventory().CreateInInventory("HuntingBag");

        UnitTest_AddMoneyToPlayer(player, 2147483647, {"USD"});
        UnitTest_RemoveMoneyAmountFromPlayer(player, 2147483647, {"USD"});
        UnitTest_AddMoneyToPlayer(player, 333999777, {"EUR"});
        UnitTest_RemoveMoneyAmountFromPlayer(player, 333999777, {"EUR"});
    }

    void UnitTest_AddMoneyToPlayer(PlayerBase player, int amountToAdd, TStringArray acceptedCurrencyTypes = null)
    {
        // Create a mock currencySetting object
        TraderPlusCurrencySettings currencySetting = new TraderPlusCurrencySettings();
        
        // Add some currency types to the currencySetting object
        TraderPlusCurrencyType currencyType1 = new TraderPlusCurrencyType("EUR");
        currencyType1.AddCurrency("TraderPlus_Money_Euro100", 100000);
        currencyType1.AddCurrency("TraderPlus_Money_Euro50", 500);
        currencyType1.AddCurrency("TraderPlus_Money_Euro10", 100);
        currencyType1.AddCurrency("TraderPlus_Money_Euro5", 50);
        currencyType1.AddCurrency("TraderPlus_Money_Euro1", 1);
        TraderPlusCurrencyType currencyType2 = new TraderPlusCurrencyType("USD");
        currencyType2.AddCurrency("TraderPlus_Money_Dollar100", 100000);
        currencyType2.AddCurrency("TraderPlus_Money_Dollar50", 500);
        currencyType2.AddCurrency("TraderPlus_Money_Dollar10", 100);
        currencyType2.AddCurrency("TraderPlus_Money_Dollar5", 50);
        currencyType2.AddCurrency("TraderPlus_Money_Dollar1", 1);
        currencySetting.currencyTypes.Insert(currencyType1);
        currencySetting.currencyTypes.Insert(currencyType2);
        
        // Call the method being tested and store the result
        TraderPlusCurrencyModule module = TraderPlusCurrencyModule.Cast(CF_ModuleCoreManager.Get(TraderPlusCurrencyModule));
	    if(!module)
        {
           GetTraderPlusCoreLogger().LogDebug("[UNIT TEST] UnitTest_AddMoneyToPlayer: FAIL");
            return;
        }
        module.SetCurrencySettings(currencySetting);
        module.AddMoneyToPlayer(player, amountToAdd, acceptedCurrencyTypes);
        
        // Check if the correct currency items were added to the player's inventory
        int playerMoney = module.GetPlayerMoneyFromAllCurrency(player);
        
        // Assert that the correct currency items were added
        if(playerMoney == amountToAdd)
        {
           GetTraderPlusCoreLogger().LogDebug("[UNIT TEST] UnitTest_AddMoneyToPlayer: PASS");
        }
        else
        {
           GetTraderPlusCoreLogger().LogDebug("[UNIT TEST] UnitTest_AddMoneyToPlayer: FAIL");
        }
    }
    
    void UnitTest_RemoveMoneyAmountFromPlayer(PlayerBase player, int amountToRemove, TStringArray acceptedCurrencyTypes = null)
    {
        // Create a mock currencySetting object
        TraderPlusCurrencySettings currencySetting = new TraderPlusCurrencySettings();
        
        // Add some currency types to the currencySetting object
        TraderPlusCurrencyType currencyType1 = new TraderPlusCurrencyType("EUR");
        currencyType1.AddCurrency("TraderPlus_Money_Euro100", 100000);
        currencyType1.AddCurrency("TraderPlus_Money_Euro50", 500);
        currencyType1.AddCurrency("TraderPlus_Money_Euro10", 100);
        currencyType1.AddCurrency("TraderPlus_Money_Euro5", 50);
        currencyType1.AddCurrency("TraderPlus_Money_Euro1", 1);
        TraderPlusCurrencyType currencyType2 = new TraderPlusCurrencyType("USD");
        currencyType2.AddCurrency("TraderPlus_Money_Dollar100", 100000);
        currencyType2.AddCurrency("TraderPlus_Money_Dollar50", 500);
        currencyType2.AddCurrency("TraderPlus_Money_Dollar10", 100);
        currencyType2.AddCurrency("TraderPlus_Money_Dollar5", 50);
        currencyType2.AddCurrency("TraderPlus_Money_Dollar1", 1);
        currencySetting.currencyTypes.Insert(currencyType1);
        currencySetting.currencyTypes.Insert(currencyType2);
        
        // Call the method being tested and store the result
        TraderPlusCurrencyModule module = TraderPlusCurrencyModule.Cast(CF_ModuleCoreManager.Get(TraderPlusCurrencyModule));
	    if(!module)
        {
           GetTraderPlusCoreLogger().LogDebug("[UNIT TEST] UnitTest_RemoveMoneyAmountFromPlayer: FAIL");
        return;
        }
        module.SetCurrencySettings(currencySetting);

        // Get Money amount before removing it
        int playerMoneyBefore = module.GetPlayerMoneyFromAllCurrency(player);

        bool result = module.RemoveMoneyAmountFromPlayer(player, amountToRemove, acceptedCurrencyTypes);

        // Get Money amount after removing it
        int playerMoneyAfter = module.GetPlayerMoneyFromAllCurrency(player);
        
        // Assert that CurrencyClass1 has been removed and CurrencyClass2 is not changed
        if(playerMoneyAfter == (playerMoneyBefore - amountToRemove))
        {
           GetTraderPlusCoreLogger().LogDebug("[UNIT TEST] UnitTest_RemoveMoneyAmountFromPlayer: PASS");
        }
        else
        {
           GetTraderPlusCoreLogger().LogDebug("[UNIT TEST] UnitTest_RemoveMoneyAmountFromPlayer: FAIL");
        }
    }

    //----------------------------------------------------------------//
	//UnitTest Methods
	//----------------------------------------------------------------//
    override void OnMissionStart(Class sender, CF_EventArgs args)
	{
		super.OnMissionStart(sender, args);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(StartUnitTest, 1000);
	}
}
