class TraderPlusBankHelpers
{
	static void SendBankAccountInfo(PlayerBase player)
	{
		#ifdef TRADERPLUSDEBUG
		GetTraderPlusLogger().LogInfo("SendBankAccountInfo");
		#endif
		if(player.m_BankAccount)
			player.m_BankAccount.UpdateAccount(player);
	}

	static void SetAmountBankAccount(PlayerBase player, int amount)
	{
		#ifdef TRADERPLUSDEBUG
		GetTraderPlusLogger().LogInfo("SetAmountBankAccount");
		#endif
		TraderPlusBankingData account = player.GetBankAccount();
		if(account)
		{
			account.MoneyAmount = amount;
			account.UpdateAccount(player);
		}
	}
};
