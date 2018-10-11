class CfgMods
{
	class simplekilllogger
	{
	    dir = "simplekilllogger";
	    picture = "";
	    action = "";
	    hideName = 1;
	    hidePicture = 1;
	    name = "simplekilllogger";
	    credits = "zalexki, DayzModders discord";
	    author = "zalexki";
	    authorID = "0";
	    version = "1.0";
	    extra = 0;
	    type = "mod";

	    dependencies[] = {"Game", "World", "Mission"};

	    class defs
	    {
            class gameScriptModule
            {
                value = "";
                files[] = {"zalexki/simplekilllogger/scripts/3_Game"};
            };
            
	        class worldScriptModule
            {
                value = "";
                files[] = {"zalexki/simplekilllogger/scripts/4_World"};
            };

            class missionScriptModule
            {
                value = "";
                files[] = {"zalexki/simplekilllogger/scripts/5_Mission"};
            };
        };
    };
};