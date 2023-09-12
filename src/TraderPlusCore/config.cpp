////////////////////////////////////////////////////////////////////
//DeRap: TraderPlusCore\config.bin
//Produced from mikero's Dos Tools Dll version 8.57
//https://mikero.bytex.digital/Downloads
//'now' is Mon May 29 15:45:34 2023 : 'file' last modified on Thu Jan 01 01:00:01 1970
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class TraderPlusCore_Script
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {};
	};
};
class CfgMods
{
	class TraderPlusCore
	{
		dir = "TraderPlusCore";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "TraderPlusCore";
		credits = "TheDmitri,Chubby,Morty";
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
				files[] = {"_UAPIBase/scripts/Common","MuchCarKey/Scripts/Common","MuchCarKeyDefines/scripts/Common","CLDefine/scripts/Common","TPDefine/scripts/Common","TM/Trader/scripts/defines","CarCover/Scripts/Common","TPDefine/scripts/Common","TraderPlusCore/scripts/Common","TraderPlusCore/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"_UAPIBase/scripts/Common","MuchCarKey/Scripts/Common","MuchCarKeyDefines/scripts/Common","CLDefine/scripts/Common","TPDefine/scripts/Common","TM/Trader/scripts/defines","CarCover/Scripts/Common","TPDefine/scripts/Common","TraderPlusCore/scripts/Common","TraderPlusCore/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"_UAPIBase/scripts/Common","MuchCarKey/Scripts/Common","MuchCarKeyDefines/scripts/Common","CLDefine/scripts/Common","TPDefine/scripts/Common","TM/Trader/scripts/defines","CarCover/Scripts/Common","TPDefine/scripts/Common","TraderPlusCore/scripts/Common","TraderPlusCore/scripts/5_Mission"};
			};
		};
	};
};