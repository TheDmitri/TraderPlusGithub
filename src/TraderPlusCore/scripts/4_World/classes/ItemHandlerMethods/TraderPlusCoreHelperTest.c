
[CF_RegisterModule(TradePlusCoreHelperModuleTest)]
class TradePlusCoreHelperModuleTest: CF_ModuleWorld
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

        UnitTest_CreateInInventory(player);
        UnitTest_CreateInCargos(player);
        UnitTest_GetTotalQuantityOfItem(player);
        UnitTest_RemoveOurProduct(player);
        UnitTest_RemoveItem(player);
    }

    void UnitTest_CreateInInventory(PlayerBase player)
    {
        string className = "Rag";
        int quantity = 5;

        // Act
        ItemBase result = TraderPlusCoreHelper.CreateInInventory(player, className, quantity);

        if(!result)
        {
           GetTraderPlusCoreLogger().LogDebug("[UNIT TEST] UnitTest_CreateInInventory: FAILED => item is null so not created");
            return;
        }

        if(TraderPlusCoreHelper.GetItemAmount(result) == quantity)
        {
           GetTraderPlusCoreLogger().LogDebug("[UNIT TEST] UnitTest_CreateInInventory: PASS");
        }
        else
        {
           GetTraderPlusCoreLogger().LogDebug(string.Format("[UNIT TEST] UnitTest_CreateInInventory: FAIL => expected : %1 got %2", quantity, TraderPlusCoreHelper.GetItemAmount(result)));
        }
    }

    void UnitTest_CreateInCargos(PlayerBase player)
    {
        string className = "BakedBeansCan";
        int quantity = 1;

        // Act
        ItemBase result = TraderPlusCoreHelper.CreateInCargos(player, className, quantity);

        if(!result)
        {
           GetTraderPlusCoreLogger().LogDebug("[UNIT TEST] UnitTest_CreateInCargos: FAILED => item is null so not created");
            return;
        }

        if(result)
        {
           GetTraderPlusCoreLogger().LogDebug("[UNIT TEST] UnitTest_CreateInCargos: PASS");
        }
        else
        {
           GetTraderPlusCoreLogger().LogDebug("[UNIT TEST] UnitTest_CreateInCargos: FAIL");
        }
    }

    void UnitTest_GetTotalQuantityOfItem(PlayerBase player)
    {
        string className = "SpaghettiCan";
        int health = TraderPlusItemState.WORN;

        // Create some items to be added to the player's inventory
        ItemBase item1 = TraderPlusCoreHelper.CreateInInventory(player, className, 1, health);

        ItemBase item2 = TraderPlusCoreHelper.CreateInInventory(player, className, 1, health);

        ItemBase item3 = TraderPlusCoreHelper.CreateInInventory(player, className, 1, TraderPlusItemState.DAMAGED);// This item should be skipped

        // Act
        int result = TraderPlusCoreHelper.GetTotalQuantityOfItem(player, className, health);

        if(result == 2)
        {
           GetTraderPlusCoreLogger().LogDebug("[UNIT TEST] UnitTest_GetTotalQuantityOfItem: PASS");
        }
        else
        {
           GetTraderPlusCoreLogger().LogDebug("[UNIT TEST] UnitTest_GetTotalQuantityOfItem: FAIL");
        }
    }

    void UnitTest_RemoveOurProduct(PlayerBase player)
    {
        // Arrange
        string className = "TraderPlus_Money_Euro10";
        int quantity = 10;
        int health = TraderPlusItemState.PRISTINE;

        // Create some items to be added to the player's inventory
        ItemBase item1 = TraderPlusCoreHelper.CreateInInventory(player, className, quantity, health);

        ItemBase item2 = TraderPlusCoreHelper.CreateInInventory(player, className, quantity, health);

        ItemBase item3 = TraderPlusCoreHelper.CreateInInventory(player, className, quantity, TraderPlusItemState.DAMAGED);// This item should be skipped

        TraderPlusCurrencyModule module = TraderPlusCurrencyModule.Cast(CF_ModuleCoreManager.Get(TraderPlusCurrencyModule));
	    if(!module)
            return;
        
        int moneyAmount = module.GetPlayerMoneyFromAllCurrency(player);
        // Act
        bool result = TraderPlusCoreHelper.RemoveOurProduct(player, className, quantity, health);

        moneyAmount = module.GetPlayerMoneyFromAllCurrency(player);

        // Assert
        // Check if the item removal was successful
        if(result && TraderPlusCoreHelper.GetTotalQuantityOfItem(player, className, health) == 20)
        {
           GetTraderPlusCoreLogger().LogDebug("[UNIT TEST] UnitTest_RemoveOurProduct: PASS");
        }
        else
        {
           GetTraderPlusCoreLogger().LogDebug(string.Format("[UNIT TEST] UnitTest_RemoveOurProduct: FAIL => expected: %1 and %2 vs %3 and %4", true, 20, result, TraderPlusCoreHelper.GetTotalQuantityOfItem(player, className, health) ));
        }
    }

    void UnitTest_RemoveItem(PlayerBase player)
    {
        // Arrange
        string className = "TraderPlus_Money_Euro50";
        ItemBase item = TraderPlusCoreHelper.CreateInInventory(player, className);
        int quantity = 2;

        // Act
        bool result = TraderPlusCoreHelper.RemoveItem(player, item, quantity);

        // Assert
        // Check if the item removal was successful
        if(result)
        {
           GetTraderPlusCoreLogger().LogDebug("[UNIT TEST] UnitTest_RemoveItem: PASS");
        }
        else
        {
           GetTraderPlusCoreLogger().LogDebug("[UNIT TEST] UnitTest_RemoveItem: FAIL");
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
