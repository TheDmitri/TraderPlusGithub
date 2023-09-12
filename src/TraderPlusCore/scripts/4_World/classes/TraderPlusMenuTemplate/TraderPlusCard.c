/*class TraderPlusCard extends UIScriptedMenu
{
    Widget wParent;

    Widget wRootCard;

    ref TraderPlusItem traderPlusItem;

    void TraderPlusCard(TraderPlusItem tpItem, Widget parent)
    {
        traderPlusItem = tpItem;
        wParent = parent;

        CreateWidget();
    }

    void CreateWidget()
    {
        wRootCard = GetGame().GetWorkspace().CreateWidgets( GetCardLayout(), wParent);
    }

    string GetCardLayout()
    {
        return "TraderPlusCore/gui/Card.layout";
    }

    void Delete()
    {
        delete this;
    }
}*/