/*class TraderPlusMenuTemplate extends UIScriptedMenu
{
    private const float UI_REFRESH_RATE = 0.05;
    private ref Widget wRootWidget;
    private ref EditBoxWidget wEditBoxSearch;
    private ref GridSpacerWidget wItemsGrid;
    private ref array<ref TraderPlusCard> wItemCards;

    string searchFilter;
    string previousSearchFilter;

    private float updateTimer;

    void TraderPlusMenuTemplate()
    {
        // Constructor
        wItemCards = new array<ref TraderPlusCard>();
    }

    void ~TraderPlusMenuTemplate()
    {
        // Destructor
        ClearCardList();
    }

    void ClearCardList()
    {
        for(int i = wItemCards.Count() - 1; i >= 0; i--)
        {
            TraderPlusCard card = wItemCards[i];
            wItemCards.RemoveOrdered(i);
            card.Delete();
        }
    }

    override Widget Init()
    {
        layoutRoot = GetGame().GetWorkspace().CreateWidgets("TraderPlusCore\datasets\gui\menuTemplate.layout");
        
        wRootWidget = layoutRoot.FindAnyWidget("rootFrame");
        wEditBoxSearch = EditBoxWidget.Cast(layoutRoot.FindAnyWidget("editBoxSearch"));
        wItemsGrid = GridSpacerWidget.Cast(layoutRoot.FindAnyWidget("itemsGrid"));
        
        return layoutRoot;
    }

    void Refresh()
    {

    }

    override void Update(float timeslice)
	{
        updateTimer += timeslice;
        if(updateTimer < UI_UPDATE_TIMER)
            return;

        searchFilter = wEditBoxSearch.GetText();
        if(searchFilter == string.Empty)
            return;

        FilterItemList();
        UpdateCardList();
    }

    void FilterItemList()
    {
        array<ref TraderPlusItem> itemList = GetItemList();
        array<ref TraderPlusItem> newItemList = new array<ref TraderPlusItem>();
        foreach(TraderPlusItem tpItem: itemList)
        {
            string itemClassName = TraderPlusCoreHelper.GetDisplayName(tpItem.className);
            if(!TraderPlusCoreHelper.ContainsIgnoreCase(itemClassName, searchFilter))
                continue;
            
            newItemList.Insert(tpItem);
        }

        SetItemList(newItemList);
    }

    array<ref TraderPlusItem> GetItemList()
    {
        return new array<TraderPlusItem>();
    } 

    void UpdateCardList()
    {
        ClearCardList();
        array<ref TraderPlusItem> itemList = GetItemList();
        foreach(TraderPlusItem tpItem: itemList)
        {
            TraderPlusCard card = new TraderPlusCard(tpItem, this);
            wItemCards.Insert(card);
        }
    }

    void SortItems()
    {
        
    }
}*/
