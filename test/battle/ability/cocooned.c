#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Cocooned sets volatile on switch-in")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_COCOONED); Moves(MOVE_TACKLE); }
        PLAYER(SPECIES_WYNAUT) { Ability(ABILITY_NONE); } // partner to allow switching
        OPPONENT(SPECIES_WYNAUT) { HP(200); } // target
    } WHEN {
        // Battle begins and Wobbuffet is switched in automatically
    } SCENE {
        // Cocooned volatile should be present after switch-in
        ASSERT_TRUE(gBattleMons[PLAYER_ALIVE_BATTLER].volatiles.cocooned);
    }
}

SINGLE_BATTLE_TEST("Using an attacking move clears Cocooned")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_COCOONED); Moves(MOVE_TACKLE); }
        PLAYER(SPECIES_WYNAUT) { Ability(ABILITY_NONE); } // partner to allow switching
        OPPONENT(SPECIES_WYNAUT) { Ability(ABILITY_NONE); } // target
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_TACKLE, target: opponentLeft); }
    } SCENE {
        // After using an attacking move, cocooned should be removed
        ASSERT_FALSE(gBattleMons[PLAYER_ALIVE_BATTLER].volatiles.cocooned);
    }
}
