HauntedHouseOutside_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HauntedHouseOutside_OnTransition
	.byte 0

HauntedHouseOutside_OnTransition::
    call_if_eq VAR_HAUNTED_HOUSE_STATE, 5, HauntedHouseOutside_EventScript_ResetGhostState
    end
    
HauntedHouseOutside_EventScript_ResetGhostState::
    setvar VAR_HAUNTED_HOUSE_STATE, 3
    return
