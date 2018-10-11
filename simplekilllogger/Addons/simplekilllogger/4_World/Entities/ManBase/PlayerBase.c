modded class PlayerBase
{
    ref SimpleKillLogger SKL;

    override void EEKilled( Object killer )
    {
        ref SurvivorBase sbKilled = this;
        ref SurvivorBase sbKiller = killer;
        ref Man manKiller = killer;

        if (GetGame().IsServer()) {
            if (manKiller.IsMan() && sbKiller.GetPlayerID() != sbKilled.GetPlayerID()) {
                SKL.KillHandler(sbKiller.GetPlayerID());
            }
            SKL.DeathHandler(sbKilled.GetPlayerID());
        }

        if( GetInstanceType() == DayZPlayerInstanceType.INSTANCETYPE_CLIENT ) {
            // @NOTE: this branch does not happen, EEKilled is called only on server
            if ( GetGame().GetPlayer() == this ) {
                super.EEKilled( killer );
            }
            if (GetHumanInventory().GetEntityInHands())
                GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ServerDropEntity,1000,false,( GetHumanInventory().GetEntityInHands() ));
        }
        else if( GetInstanceType() == DayZPlayerInstanceType.INSTANCETYPE_SERVER)//server
        {
            if( GetBleedingManager() ) delete GetBleedingManager();
            if( GetHumanInventory().GetEntityInHands() )
                GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ServerDropEntity,1000,false,( GetHumanInventory().GetEntityInHands() ));
        }

        if ( GetSoftSkillManager() ) {
            delete GetSoftSkillManager();
        }

        GetStateManager().OnPlayerKilled();

        // kill character in database
        if (GetHive()) {
            GetHive().CharacterKill(this);
        }
    }

    override void OnConnect()
    {
        Debug.Log("Player connected:"+this.ToString(),"Connect");

        ref SurvivorBase sb = this;
        sb.SetPlayerID(this.GetIdentity().GetPlainId());
        sb.SetPlayerFullName(this.GetIdentity().GetName());

        SKL = new SimpleKillLogger;
        SKL.OnConnectHandler(sb.GetPlayerID(), sb.GetPlayerFullName());

        // NEW STATS API
        StatRegister("playtime");
        StatRegister("dist");
    }
}