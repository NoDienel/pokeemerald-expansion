#include "global.h"
#include "test/battle.h"

DOUBLE_BATTLE_TEST("Toggle Mode swaps Attack and Sp. Attack each end of turn and resets on switch")
{
    s16 dmg1;
    s16 dmg2;
    s16 dmg3;

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_TOGGLE_MODE); Attack(50); SpAttack(100); Moves(MOVE_TACKLE); }
        PLAYER(SPECIES_WYNAUT) { Ability(ABILITY_NONE); } // partner to allow switching
        OPPONENT(SPECIES_WYNAUT) { HP(200); } // target
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_TACKLE, target: opponentLeft); }
    } SCENE {
        HP_BAR(opponentLeft, captureDamage: &dmg1);
    }

    WHEN {
        TURN { MOVE(playerLeft, MOVE_TACKLE, target: opponentLeft); }
    } SCENE {
        HP_BAR(opponentLeft, captureDamage: &dmg2);
    } THEN {
        EXPECT_GT(dmg2, dmg1);
    }

    WHEN {
        TURN { SWITCH(playerLeft, 1); }
    }

    WHEN {
        TURN { SWITCH(playerLeft, 0); MOVE(playerLeft, MOVE_TACKLE, target: opponentLeft); }
    } SCENE {
        HP_BAR(opponentLeft, captureDamage: &dmg3);
    } THEN {
        // After switching out and back, Toggle Mode should be reset so damage should return to original
        EXPECT_EQ(dmg3, dmg1);
    }
}
