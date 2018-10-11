static string SKLDataFileLocation = "$profile:SKL.json";

class SimpleKillLogger
{
    ref map<string, map<string, string>> skl_data = new map<string, map<string, string>>();

    map<string, map<string, string>> Load()
    {
        ref map<string, map<string, string>> data = new map<string, map<string, string>>();

        if ( FileExist(SKLDataFileLocation) ) {
            JsonFileLoader<map<string, map<string, string>>>.JsonLoadFile(SKLDataFileLocation, data);
        } else {
            JsonFileLoader<map<string, map<string, string>>>.JsonSaveFile(SKLDataFileLocation, data);
        }

        return data;
    }

    void ChatAllLeaderboard()
    {
        skl_data = Load();
        foreach (map<string, string> player : skl_data) {
            GetGame().ChatPlayer( 0, player.Get("name") + " kill: " + player.Get("kill") + " death: " + player.Get("death"));
        }
    }

    void OnConnectHandler(string id, string name)
    {
        skl_data = Load();
        ref map<string, string> player = new map<string, string>();

        player.Set("name", name);
        skl_data.Insert(id, player);
        Save(skl_data);
    }

    void DeathHandler(string id)
    {
        skl_data = Load();
        ref map<string, string> player = new map<string, string>();

        if (skl_data.Contains(id)) {
            player = skl_data.Get(id);
            if (player.Contains("death")) {
                int death = player.Get("death").ToInt();
                death = death + 1;
                player.Set("death", death.ToString());
            } else {
                player.Set("death", "1");
            }
        } else {
            player.Set("death", "1");
        }

        skl_data.Insert(id, player);
        Save(skl_data);
    }

    void KillHandler(string id)
    {
        skl_data = Load();
        ref map<string, string> player = new map<string, string>();

        if (skl_data.Contains(id)) {
            player = skl_data.Get(id);
            if (player.Contains("kill")) {
                int kill = player.Get("kill").ToInt();
                kill = kill + 1;
                player.Set("kill", kill.ToString());
            } else {
                player.Set("kill", "1");
            }
        } else {
            player.Set("kill", "1");
        }

        skl_data.Insert(id, player);
        Save(skl_data);
    }

    void Save(map<string, map<string, string>> skl_data)
    {
        JsonFileLoader<map<string, map<string, string>>>.JsonSaveFile(SKLDataFileLocation, skl_data);
    }
}
