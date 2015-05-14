/*
         OnPlayerAttachTrailer [v1.0]
      (c) Copyright 2013-2015 by Inferno
 
	  @author    : Inferno <inferno.piotr@gmail.com> (http://www.infus211.ct8.pl)
	  @website	 : www.PTSRP.pl
	  @date      : 14 may 2015
	  @update    : 14 may 2015

	  Instructions:
	  - Add this in oryginal publics:
	  		opat_OnPlayerUpdate(playerid); 
	  		opat_OnPlayerStateChange(playerid, newstate, oldstate);
	  		opat_OnPlayerConnect(playerid);
	  - Add anywhere in your gamemode new public OnPlayerAttachTrailer(playerid, vehicleid, trailerid, status)
	  - READY!
  
 */ 

#define ATTACHED_TRAILER 	0
#define DEATTACHED_TRAILER 	1

forward OnPlayerAttachTrailer(playerid, vehicleid, trailerid, status);

new opat_PlayerVehicleID[MAX_PLAYERS],
	opat_PlayerState[MAX_PLAYERS],
	opat_VehicleInfoTrailer[MAX_VEHICLES];

public OnPlayerUpdate(playerid) {
	if(opat_PlayerVehicleID[playerid] != -1 && opat_PlayerState[playerid] == PLAYER_STATE_DRIVER) {
		if(opat_VehicleInfoTrailer[ opat_PlayerVehicleID[playerid] ] == 0) {
			if(GetVehicleTrailer(opat_PlayerVehicleID[playerid]) != 0) {
				opat_VehicleInfoTrailer[ opat_PlayerVehicleID[playerid] ] = GetVehicleTrailer(opat_PlayerVehicleID[playerid]);
				CallRemoteFunction("OnPlayerAttachTrailer", "iiii", playerid, opat_PlayerVehicleID[playerid], opat_VehicleInfoTrailer[ opat_PlayerVehicleID[playerid] ], ATTACHED_TRAILER);
			}
		} else {
			if(GetVehicleTrailer(opat_PlayerVehicleID[playerid]) == 0) {
				opat_VehicleInfoTrailer[ opat_PlayerVehicleID[playerid] ] = 0;
				CallRemoteFunction("OnPlayerAttachTrailer", "iiii", playerid, opat_PlayerVehicleID[playerid], 0, DEATTACHED_TRAILER);
			}
		}
	}
	return 1;
}

#if defined _ALS_OnPlayerUpdate
    #undef OnPlayerUpdate
#else
    #define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate opat_OnPlayerUpdate
forward opat_OnPlayerUpdate();

public OnPlayerStateChange(playerid, newstate, oldstate) {
	opat_PlayerState[playerid] = newstate;
	if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER) {
		if(oldstate == PLAYER_STATE_ONFOOT) {
			opat_PlayerVehicleID[playerid] = GetPlayerVehicleID(playerid);
			opat_VehicleInfoTrailer[ opat_PlayerVehicleID[playerid] ] = GetVehicleTrailer(opat_PlayerVehicleID[playerid]);
		}
	}

	if(newstate == PLAYER_STATE_ONFOOT) {
		if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER) {
			opat_PlayerVehicleID[playerid] = -1;
		}
	}
	return 1;
}

#if defined _ALS_OnPlayerStateChange
    #undef OnPlayerStateChange
#else
    #define _ALS_OnPlayerStateChange
#endif
#define OnPlayerStateChange opat_OnPlayerStateChange
forward opat_OnPlayerStateChange();

public OnPlayerConnect(playerid) {
	opat_PlayerVehicleID[playerid] = -1;
	return 1;
}

#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect opat_OnPlayerConnect
forward opat_OnPlayerConnect();