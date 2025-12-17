# Gamepad data base source
This file describes how  gamepad database is created/modified

We have taken gamecontroller databse from below   
1-  https://github.com/libsdl-org/SDL  gamedb 
 ( https://github.com/libsdl-org/SDL/blob/main/src/joystick/SDL_gamepad_db.h ) 

2- https://github.com/gabomdq/SDL_GameControllerDB
 ( https://github.com/gabomdq/SDL_GameControllerDB/blob/master/gamecontrollerdb.txt ) 
 
Taken only Linux mapping 
Removed duplicate  entries 

just run below script, it will generate gamecontrollerdb 
$update-gamecontrollerdb.sh

Modified some entries for RDK which are kept at the begining 

# DataBase mapping in RDK 
 These are hand picked mappings
 1-8BitDo Lite ( designed for Nintendo Pro mode ) 
    slide centre button to side left( named as S. S for SWITCH) to conect as Nindendo Mode ( prefered Mode )
    slide centre button to side right ( named as X. X as X Box  Mode )  to connect as X Box controller mode ( Not encouraged )  
 2-8BitDo SN30 Pro ( designed for Nintendo Pro mode ) 
     Similar as 1

 3-RedStorm gamer Choice  (designed for Pro Mode )
     Pro Mode: Y + START button 
     No Other mdoe supported
 4-XBox 1708 
    Xbox Wireless Controller v903 all key works based on latets changes from BLE 

5-echtpower controller ( designed for Pro Mode )
    Pro Mode: Y + START

6-Gamesir T4 Pro 
    A + START button : gamesir T4 Pro mode
    HOME button does not work 
