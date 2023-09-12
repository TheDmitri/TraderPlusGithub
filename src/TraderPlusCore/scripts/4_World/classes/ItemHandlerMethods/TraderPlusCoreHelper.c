class TraderPlusCoreHelper
{

  /*Function that allows to get the player variable from its identity => used for RPC*/
  static PlayerBase GetPlayerByIdentity(PlayerIdentity sender)
  {
    int	low	 =	0;
    int	high =	0;
    GetGame().GetPlayerNetworkIDByIdentityID( sender.GetPlayerId(), low, high );
    return PlayerBase.Cast( GetGame().GetObjectByNetworkId(low, high ));
  }

  static int GetItemAmount(ItemBase item)
  {
    int amount = 1;

    if (item.HasQuantity())
    {
      Magazine mag;
      if (Class.CastTo(mag, item))
        amount = mag.GetAmmoCount();
      else
        amount = item.GetQuantity();
    }
    return amount;
  }

  static ItemBase AddQuantity(ItemBase item, int quantity)
  {
    Magazine mag = Magazine.Cast(item);
    if (mag)
        mag.ServerSetAmmoCount(mag.GetAmmoCount() + quantity);
    else
      item.SetQuantity((QuantityConversions.GetItemQuantity(item) + quantity));
    return item;
  }

  static ItemBase SetQuantity(ItemBase item, int amount)
  {
    Magazine mag = Magazine.Cast(item);
    if (mag)
        mag.ServerSetAmmoCount(amount);
    else
      item.SetQuantity(amount);
    return item;
  }

  static int GetMaxItemQuantityServer(string className)
  {
    EntityAI ent = EntityAI.Cast(GetGame().CreateObject(className , "0 0 0"));
    if(!ent)
      return 0;

    ItemBase item;
    if(Class.CastTo(item, ent))
    {
      float currentQuantity, minQuantity, maxQuantity;
      QuantityConversions.GetItemQuantity(item, currentQuantity, minQuantity, maxQuantity);

      if(maxQuantity == 0){
        maxQuantity = 1;
      }
            
      GetGame().ObjectDelete(item);
      return maxQuantity;
    }

    GetGame().ObjectDelete(ent);
    return 0;
  }

  static string TrimUnt(string input)
  {
      input.Replace("$UNT$", "");
      return input;
  }

  static string GetDisplayName(string className)
  {
    string displayName = className;

    if (GetGame().ConfigGetText(CFG_VEHICLESPATH + " " + className + " displayName", displayName))
    {
      displayName = TrimUnt(displayName);
    }

    if (GetGame().ConfigGetText(CFG_WEAPONSPATH + " " + className + " displayName", displayName))
    {
      displayName = TrimUnt(displayName);
    }

    if (GetGame().ConfigGetText(CFG_MAGAZINESPATH + " " + className + " displayName", displayName))
    {
      displayName = TrimUnt(displayName);
    }

    return displayName;
  }

  static bool ContainsIgnoreCase(string source, string key)
  {
    source.ToLower();
    key.ToLower();

    return source.Contains(key);
  }

  static float GetDamageStateFromLevel(int level)
  {
  	switch(level)
  	{
  		case GameConstants.STATE_PRISTINE:
  			return GameConstants.DAMAGE_PRISTINE_VALUE;
  			break;

  		case GameConstants.STATE_BADLY_DAMAGED:
  			return GameConstants.DAMAGE_BADLY_DAMAGED_VALUE;
  			break;

  		case GameConstants.STATE_DAMAGED:
  			return GameConstants.DAMAGE_DAMAGED_VALUE;
  			break;

  		case GameConstants.STATE_WORN:
  			return GameConstants.DAMAGE_WORN_VALUE;
  			break;

  		case GameConstants.STATE_RUINED:
  			return GameConstants.DAMAGE_RUINED_VALUE;
  			break;

  		default: return GameConstants.DAMAGE_PRISTINE_VALUE;
  			break;
  	}
	   return GameConstants.DAMAGE_PRISTINE_VALUE;
  }

  static void EmptyMag(PlayerBase player, Magazine mag)
    {
        #ifdef TRADERPLUSDEBUG
        GetTraderPlusLogger().LogInfo("EmptyMag function:");
        #endif
        float dmg;
        string ammoType;
        int quantity = mag.GetAmmoCount();

        // Gather ammo types, quantites and health
        TStringArray ammoKeys = new TStringArray;
        TStringArray ammoTypes = new TStringArray;
        TFloatArray damages = new TFloatArray;
        TIntArray quantites = new TIntArray;
        for (int i = 0; i < quantity; ++i)
        {
            if ( !mag.ServerAcquireCartridge(dmg,ammoType) )
                break;

            float roundDmg = Math.Round(dmg * 1000)/1000;
            string ammoKey = string.Format("%1_%2", ammoType, roundDmg);
            int bulletIndex = ammoKeys.Find(ammoKey);
            if (bulletIndex == -1)
            {
                ammoKeys.Insert(ammoKey);
                damages.Insert(roundDmg);
                quantites.Insert(1);
                ammoTypes.Insert(ammoType);
                continue;
            }
            quantites.Set(bulletIndex, quantites.Get(bulletIndex) + 1);
        }

        // Move to inventory, or ground if inventory full
        array< Magazine > piles;
        Magazine magazinePile;
        for (int j = 0; j < ammoKeys.Count(); ++j)
        {
            float bulletsDamage = damages.Get(j);
            int bulletsCount = quantites.Get(j);
            string bulletType = ammoTypes.Get(j);

            CreateMagazinePilesFromBullet(player, bulletType,bulletsCount,bulletsDamage);
        }
    }

    static array<Magazine> CreateMagazinePilesFromBullet(PlayerBase player,string bullet_type, float quantity, float bulletsDamage )
    {
      #ifdef TRADERPLUSDEBUG
      GetTraderPlusLogger().LogInfo("CreateMagazinePilesFromBullet:"+quantity);
      #endif
      array<Magazine> items = new array<Magazine>;
      string item_name;
      if( !g_Game.ConfigGetText("cfgAmmo " + bullet_type + " spawnPileType", item_name) )
          return items;

      float stack_size = g_Game.ConfigGetInt("cfgMagazines " + item_name + " count");

      if(stack_size > 0)
      {
          Magazine pile;
          int piles_count = Math.Floor(quantity/stack_size);
          int rest = quantity - (piles_count*stack_size);

          for ( int i = 0; i < piles_count; i++ )
          {
              pile = Magazine.Cast(CreateInInventory(player,item_name,stack_size, true));
              items.Insert(pile);
              SetHealthFromDamage(pile, bulletsDamage);
          }
          if ( rest > 0)
          {
              pile = Magazine.Cast(CreateInInventory(player,item_name, rest, true));
              items.Insert(pile);
              SetHealthFromDamage(pile, bulletsDamage);
          }
      }
      return items;
  }

  static void SetHealthFromDamage(Magazine pile, float bulletsDamage)
  {
      float bulletsHealth = pile.GetMaxHealth("", "") * (1.0 - bulletsDamage);
      pile.SetHealth( "", "", bulletsHealth );
  }

  static bool CanLoadMagazine(ItemBase target, ItemBase item)
	{
		Magazine ammo;
		Magazine mag;
		return ( Class.CastTo(ammo, target) && Class.CastTo(mag, item) && mag.GetAmmoCount() < mag.GetAmmoMax() && mag.IsCompatiableAmmo( ammo ) );
	}

  static bool IsMagazine(string className)
  {
    bool isMag = false;
    ItemBase item = ItemBase.Cast(GetGame().CreateObject(className, vector.Zero));
    Magazine mag;
    Ammunition_Base ammo;

    if(CastTo(mag, item) && !CastTo(ammo, item))
      isMag = true;

    GetGame().ObjectDelete(item);

    return isMag;
  }

  static int GetTotalQuantityOfItem(PlayerBase player, string className, int health = TraderPlusItemState.ALL_STATE)
  {
      if(!player)
        return 0;

  		int quantity = 0;
  		array<EntityAI> itemsArray = GetItemsArray(player);
      foreach(EntityAI entity: itemsArray)
      {
        if (CF_String.EqualsIgnoreCase(entity.GetType(),className))
        {
          ItemBase item = ItemBase.Cast(entity);
          if(ShouldSkipItem(item))
            continue;

          if(item.GetHealthLevel() == health || health == TraderPlusItemState.ALL_STATE)
            quantity+=GetItemAmount(item);
        }
      }

  		return quantity;
  }

  static ItemBase CheckForStackableItem(PlayerBase player, string className, int quantity = 1)
  {
    if(IsMagazine(className))
      return null;

    ItemBase item;
    array<EntityAI> itemsArray = GetItemsArray(player);
    array<ItemBase> stackableItems = new array<ItemBase>;
    for (int i = 0; i < itemsArray.Count(); ++i)
    {
      item = ItemBase.Cast(itemsArray[i]);
      if (item && item.GetType() == className)
      {
        float currentQuantity, minQuantity, maxQuantity;
        QuantityConversions.GetItemQuantity(item, currentQuantity, minQuantity, maxQuantity);

        if (maxQuantity==0){
          currentQuantity = 1;
          maxQuantity = 1;
        }

        if ((currentQuantity + quantity) <= maxQuantity)
          stackableItems.Insert(item);
      }
    }

    if (stackableItems.Count() > 0){
      item = stackableItems[0];
      return AddQuantity(item, quantity);
    }

    return null;
  }

  static array<EntityAI> GetAttachments(EntityAI item)
  {
    array<EntityAI> attachments = new array<EntityAI>();
      
    Weapon_Base wpn = Weapon_Base.Cast(item);
      
    if (wpn && !StaticTraderPlusCoreLists.blackListWeaponsFromAttachments.Find(wpn.GetType()) != -1)
    {
      int slotCountCorrect = wpn.GetSlotsCountCorrect();
      for (int i = 0; i < slotCountCorrect; i++)
      {
        int slotId = wpn.GetInventory().GetAttachmentSlotId(i);
        EntityAI attachment = EntityAI.Cast(wpn.GetInventory().FindAttachment(slotId));
              
        if (attachment){
          attachments.Insert(attachment);
        }
      }
    }
      
    return attachments;
  }

  static void RecreateAllAttachments(PlayerBase player, array<EntityAI> attachments)
  {
    for(int i = 0; i< attachments.Count() ; i++)
  	{
  		ItemBase item = ItemBase.Cast(attachments[i]);
  		if(item)
  			CreateInInventory(player, item.GetType(), GetItemAmount(item), item.GetHealthLevel());
  	}
  }
  
  static ItemBase CreateInCargos(PlayerBase player, string className, int quantity = 1)
  {
    ItemBase item;
    array<EntityAI> itemsArray = GetItemsArray(player);
    for(int i = 0; i < itemsArray.Count(); i++)
    {
      if(!Class.CastTo(item, itemsArray[i]))
        continue;

      EntityAI newItem = EntityAI.Cast(item.GetInventory().CreateInInventory(className));
      if (newItem)
        return ItemBase.Cast(newItem);
    }

    return null;
  }

  static ItemBase CreateInInventory(PlayerBase player, string className, int quantity = 1, int healthLevel = TraderPlusItemState.PRISTINE)
  {
  		if(!player)
        return NULL;

      GetTraderPlusCoreLogger().LogDebug("CreateInInventory: " + className);

      int maxQuantity = GetMaxItemQuantityServer(className);
      if(quantity < 0) quantity = maxQuantity;

      if(quantity > maxQuantity)
      {
        int loopCount = quantity / maxQuantity;
        quantity -= loopCount * maxQuantity;
        GetTraderPlusCoreLogger().LogDebug("loopCount: " + loopCount.ToString());
        GetTraderPlusCoreLogger().LogDebug("quantity: " + quantity.ToString());
        for(int i = 0; i < loopCount; i++)
        {
          CreateInInventory(player, className, maxQuantity);
        }
      }

      if(quantity != 0){
        ItemBase item = CheckForStackableItem(player, className, quantity);
        if(item)
          return item;
      }

  		ItemBase newItem = ItemBase.Cast(player.GetInventory().CreateInInventory(className));

      if(!newItem){
        //GetTraderPlusCoreLogger().LogDebug("Item wasn't able to be spawned in inventory at first attempt");
        newItem = CreateInCargos(player, className, quantity);
      }

  		if (!newItem){
        //GetTraderPlusCoreLogger().LogDebug("item doesn't exist in inv => attempt creation in hand");
  			newItem = ItemBase.Cast(player.GetHumanInventory().CreateInHands(className));
      }

  		if (!newItem){
        //GetTraderPlusCoreLogger().LogDebug("item doesn't exist in inv => attempt creation in ground");
        newItem = ItemBase.Cast(player.SpawnEntityOnGroundPos(className, player.GetPosition()));
      }

  		if (newItem){
        GetTraderPlusCoreLogger().LogDebug("item exist in inventory or ground => ");
        newItem = SetHealthLevel(newItem,healthLevel);
        return SetQuantity(newItem, quantity);
      }

      GetTraderPlusCoreLogger().LogDebug("item doesn't exist at all...");

  		return null;
  }

  static array<EntityAI> GetItemsArray(PlayerBase player)
  {
    array<EntityAI> itemsArray = new array<EntityAI>();
    player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
    return itemsArray;
  }

  static bool RemoveOurProduct(PlayerBase player, string className, int quantity, int health = -1)
  {
    if (quantity < 0)
      quantity = GetMaxItemQuantityServer(className);
  
    int itemSpecificCount = GetTotalQuantityOfItem(player, className, health);
  
    if (itemSpecificCount < quantity || itemSpecificCount == 0)
    {
      GetTraderPlusCoreLogger().LogDebug("Item doesn't exist or quantity too low");
      return false;
    }
  
    array<EntityAI> itemsArray = GetItemsArray(player);
    foreach (EntityAI entity : itemsArray)
    {
      ItemBase item = ItemBase.Cast(entity);
          
      if (ShouldSkipItem(item))
        continue;
  
      if (IsMatchingItem(item, className, health))
      {
        quantity = RemoveItem(player, item, quantity);

        if(quantity <= 0)
          return true;
      }
    }
  
    return false;
  }

  static bool IsWearByPlayer(EntityAI entity)
  {
    InventoryLocation il = new InventoryLocation;
    entity.GetInventory().GetCurrentInventoryLocation( il );
    if( !il.IsValid() )return true;
      // check the direct parent (clothing will be the parent if not on man attachment)
    if (il.GetParent() && !il.GetParent().IsInherited(Man))
      return false;

    // items in hands are not worn
    if (il.GetType() == InventoryLocationType.HANDS)
      return false;

    return true;
  }
  
  static bool ShouldSkipItem(ItemBase item)
  {
    if (item == null || item.IsLockedInSlot() || IsWearByPlayer(item) || Weapon_Base.Cast(item.GetHierarchyParent()) != null)
      return true;
  
    return false;
  }

  static ItemBase SetHealthLevel(ItemBase item, int level)
  {
    item.SetHealth("","",GetDamageStateFromLevel(level)*item.GetMaxHealth());
    return item;
  }
  
  static bool IsMatchingItem(ItemBase item, string className, int health = -1)
  {
      if (item.GetType() != className)
          return false;
  
      if (item.IsKindOf("Edible_Base"))
      {
          Edible_Base edible = Edible_Base.Cast(item);
          if (edible.HasFoodStage() && edible.GetFoodStageType() != FoodStageType.RAW)
              return false;
      }
  
      if (!item.IsInherited(SurvivorBase) && (item.GetHealthLevel() == health || health == -1))
          return true;
  
      return false;
  }
  
  static int RemoveItem(PlayerBase player, ItemBase item, int quantity, bool removeAttachment = false)
  {
    GetTraderPlusCoreLogger().LogDebug(string.Format("RemoveItem:%1 qty:%2 removeattach:%3", item.GetType(), quantity, removeAttachment));
      if(!removeAttachment)
      {
        array<EntityAI> attachments = GetAttachments(item);
  
        if (attachments.Count() > 0)
          RecreateAllAttachments(player, attachments);
      }
  
    if (QuantityConversions.HasItemQuantity(item) == 0 || (item.IsInherited(Magazine) && !item.IsInherited(Ammunition_Base)))
    {
      Magazine mag = Magazine.Cast(item);
        if(mag)
          EmptyMag(player, mag);

      GetTraderPlusCoreLogger().LogDebug(string.Format("Remove item 1"));
  
        GetGame().ObjectDelete(item);
        quantity--;
    }
    else
    {
      int itemAmount = GetItemAmount(item);
  
      if (itemAmount > quantity && quantity != 0)
      {
        item = AddQuantity(item, quantity * -1);

        GetTraderPlusCoreLogger().LogDebug(string.Format("Reduce qty item 1"));
        quantity = 0;
      }
      else
      {
        quantity -= itemAmount;
        GetTraderPlusCoreLogger().LogDebug(string.Format("Reduce qty item 1 and delete"));
        GetGame().ObjectDelete(item);
      }
    }

    GetTraderPlusCoreLogger().LogDebug(string.Format("return quantity:%1", quantity));
    return quantity;
  }
}