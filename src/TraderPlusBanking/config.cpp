////////////////////////////////////////////////////////////////////
//DeRap: TraderPlusBanking\config.bin
//Produced from mikero's Dos Tools Dll version 8.57
//https://mikero.bytex.digital/Downloads
//'now' is Mon Sep 11 20:20:16 2023 : 'file' last modified on Thu Jan 01 01:00:01 1970
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class TraderPlusBanking_Script
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","TraderPlus_Script"};
	};
};
class CfgMods
{
	class TraderPlusBanking
	{
		dir = "TraderPlusBanking";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "TraderPlusBanking";
		credits = "TheDmitri";
		author = "TheDmitri";
		authorID = "0";
		version = "1.1";
		extra = 0;
		type = "mod";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"MuchCarKey/Scripts/Common","MuchCarKeyDefines/scripts/Common","CLDefine/scripts/Common","TPDefine/scripts/Common","TM/Trader/scripts/defines","CarCover/Scripts/Common","TPDefine/scripts/Common","TraderPlus/scripts/Common","TraderPlusBanking/scripts/Common","TraderPlusBanking/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"MuchCarKey/Scripts/Common","MuchCarKeyDefines/scripts/Common","CLDefine/scripts/Common","TPDefine/scripts/Common","TM/Trader/scripts/defines","CarCover/Scripts/Common","TPDefine/scripts/Common","TraderPlus/scripts/Common","TraderPlusBanking/scripts/Common","TraderPlusBanking/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"MuchCarKey/Scripts/Common","MuchCarKeyDefines/scripts/Common","CLDefine/scripts/Common","TPDefine/scripts/Common","TM/Trader/scripts/defines","CarCover/Scripts/Common","TPDefine/scripts/Common","TraderPlus/scripts/Common","TraderPlusBanking/scripts/Common","TraderPlusBanking/scripts/5_Mission"};
			};
		};
	};
};
