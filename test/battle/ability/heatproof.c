#include "global.h"
#include "test/battle.h"

DOUBLE_BATTLE_TEST("Heatproof halves Fire-type damage")
{
    s16 dmg1;
    s16 dmg2;

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_NONE); Moves(MOVE_EMBER); }
        PLAYER(SPECIES_WYNAUT) { Ability(ABILITY_NONE); } // partner to allow double
        OPPONENT(SPECIES_WYNAUT) { Ability(ABILITY_NONE); HP(200); } // left (no heatproof)
        OPPONENT(SPECIES_WYNAUT) { Ability(ABILITY_HEATPROOF); HP(200); } // right (heatproof)
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_EMBER, target: opponentLeft); }
    } SCENE {
        HP_BAR(opponentLeft, captureDamage: &dmg1);
    }

    WHEN {
        TURN { MOVE(playerLeft, MOVE_EMBER, target: opponentRight); }
    } SCENE {
        HP_BAR(opponentRight, captureDamage: &dmg2);
    } THEN {
        // Heatproof target should take less damage (roughly half)
        EXPECT_GT(dmg1, dmg2);
        EXPECT_EQ(dmg1 / 2, dmg2);
    }
}

SINGLE_BATTLE_TEST("Heatproof prevents burn from Will-O-Wisp")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_NONE); Moves(MOVE_WILL_O_WISP); }
        OPPONENT(SPECIES_WYNAUT) { Ability(ABILITY_HEATPROOF); }
    } WHEN {
        TURN { MOVE(player, MOVE_WILL_O_WISP, target: opponent); }
    } SCENE {
    } THEN {
        // Will-O-Wisp should not burn a Heatproof target
        EXPECT_FALSE(gBattleMons[B_POSITION_OPPONENT_LEFT].status1 & STATUS1_BURN);
    }
}
