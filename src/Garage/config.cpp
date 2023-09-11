////////////////////////////////////////////////////////////////////
//DeRap: Garage\config.bin
//Produced from mikero's Dos Tools Dll version 8.57
//https://mikero.bytex.digital/Downloads
//'now' is Mon Sep 11 20:20:06 2023 : 'file' last modified on Thu Jan 01 01:00:01 1970
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class Garage_Script
	{
		units[] = {"TraderPlusVehicleCargo"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","TraderPlus_Script"};
	};
};
class CfgMods
{
	class Garage
	{
		dir = "Garage";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "Garage";
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
				files[] = {"MuchCarKey/Scripts/Common","MuchCarKeyDefines/scripts/Common","CLDefine/scripts/Common","TPDefine/scripts/Common","TM/Trader/scripts/defines","CarCover/Scripts/Common","TPDefine/scripts/Common","TraderPlus/scripts/Common","Garage/scripts/Common","Garage/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"MuchCarKey/Scripts/Common","MuchCarKeyDefines/scripts/Common","CLDefine/scripts/Common","TPDefine/scripts/Common","TM/Trader/scripts/defines","CarCover/Scripts/Common","TPDefine/scripts/Common","TraderPlus/scripts/Common","Garage/scripts/Common","Garage/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"MuchCarKey/Scripts/Common","MuchCarKeyDefines/scripts/Common","CLDefine/scripts/Common","TPDefine/scripts/Common","TM/Trader/scripts/defines","CarCover/Scripts/Common","TPDefine/scripts/Common","TraderPlus/scripts/Common","Garage/scripts/Common","Garage/scripts/5_Mission"};
			};
		};
	};
};
class CfgVehicles
{
	class ReceiptBase;
	class TraderPlusVehicleCargo: ReceiptBase
	{
		scope = 2;
		displayName = "VEHICLE CARGOS SAVED";
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"TraderPlus\images\loot_paperRcpt_co.paa"};
	};
};
