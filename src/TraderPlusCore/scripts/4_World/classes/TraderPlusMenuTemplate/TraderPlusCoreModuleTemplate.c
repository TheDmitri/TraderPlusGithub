/*TraderPlusCoreModuleTemplate GetTraderPlusCoreModuleTemplate()
{
    return TraderPlusCoreModuleTemplate.Cast(CF_ModuleCoreManager.Get(TraderPlusCoreModuleTemplate));
}

[CF_RegisterModule(TraderPlusCoreModuleTemplate)]
class TraderPlusCoreModuleTemplate: CF_ModuleWorld
{
    private ref array<ref TraderPlusItem> itemList;

    ref TraderPlusMenuTemplate iTraderPlusMenuTemplate;

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
            itemList = new array<ref TraderPlusItem>();
            FillItemList(); //temp method for test
        }
        else
        {
            itemList = new array<ref TraderPlusItem>();
        }

        InitRPCs();
    }

    void InitRPCs()
    {
        if(GetGame().IsServer())
        {
            AddLegacyRPC("UpdateItemListRequest", SingleplayerExecutionType.Client);
        }
        else
        {
            AddLegacyRPC("UpdateItemListNotification", SingleplayerExecutionType.Client);
            AddLegacyRPC("UpdateItemListResponse", SingleplayerExecutionType.Client);
        }
    }

    array<ref TraderPlusItem> GetItemList()
    {
        return itemList;
    }

    //temp method for test
    void FillItemList()
    {
        for(int i=0;i<10;i++)
        {
            itemList.Insert(new TraderPlusItem("M4A1"));
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

    void UpdateItemListRequest(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if(type != CallType.Server)
            return;

        PlayerBase player = TraderPlusCoreHelper.GetPlayerIdentity(sender);
        if(player)
            GetRPCManager().SendRPC(ClassName(), "UpdateItemListResponse", new Param1<array<ref TraderPlusItem>>(itemList), true, sender);

        GetTraderPlusCoreLogger().LogDebug("UpdateItemListRequest");
    }

    void UpdateItemListNotification(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if(type != CallType.Client)
            return;

        if(iTraderPlusMenuTemplate)
            GetRPCManager().SendRPC(ClassName(), "UpdateItemListRequest", null, true, null);

        GetTraderPlusCoreLogger().LogDebug("UpdateItemListNotification");
    }

    void UpdateItemListResponse(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if(type != CallType.Client)
            return;

        Param1<array<ref TraderPlusItem>> data;
        if(!ctx.Read(data))
            return;

        itemList = data.param1;

        if(iTraderPlusMenuTemplate)
            iTraderPlusMenuTemplate.Refresh();

        GetTraderPlusCoreLogger().LogDebug("UpdateItemListResponse");
    }
}*/