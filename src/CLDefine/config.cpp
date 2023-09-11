////////////////////////////////////////////////////////////////////
//DeRap: CLDefine\config.bin
//Produced from mikero's Dos Tools Dll version 8.57
//https://mikero.bytex.digital/Downloads
//'now' is Mon Sep 11 20:20:03 2023 : 'file' last modified on Thu Jan 01 01:00:01 1970
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class CLDefine
	{
		requiredVersion = 0.1;
		requiredAddons[] = {};
		units[] = {};
		weapons[] = {};
	};
};
class CfgMods
{
	class CLDefine
	{
		dir = "CLDefine";
		name = "CL";
		type = "mod";
		dependencies[] = {"GameLib","Game","World","Mission"};
		class defs
		{
			class gameLibScriptModule
			{
				value = "";
				files[] = {"CLDefine/scripts/Common"};
			};
			class gameScriptModule
			{
				value = "";
				files[] = {"CLDefine/scripts/Common"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"CLDefine/scripts/Common"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"CLDefine/scripts/Common"};
			};
		};
	};
};
