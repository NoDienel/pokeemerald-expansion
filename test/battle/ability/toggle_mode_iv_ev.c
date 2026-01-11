#include "global.h"
#include "test/battle.h"

DOUBLE_BATTLE_TEST("Toggle Mode swaps IV/EV contributions")
{
    s16 dmg1;
    s16 dmg2;

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_TOGGLE_MODE); AttackIV(0); SpAttackIV(31); AttackIV(0); SpAttackIV(252); Moves(MOVE_TACKLE); }
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
        // On second turn Toggle Mode flips and should cause damage to change due to IV/EV swap
        EXPECT_GT(dmg2, dmg1);
    }
}
