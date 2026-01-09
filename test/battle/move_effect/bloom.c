#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveEffect(MOVE_BLOOM) == EFFECT_BLOOM);
}

SINGLE_BATTLE_TEST("Bloom sets Blooming volatile and heals Grass user at end of turn")
{
    GIVEN {
        PLAYER(SPECIES_ODDISH) { HP(150); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BLOOM); }
        TURN {}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLOOM, player);
        HP_BAR(player, captureDamage: &results[0].heal);
    } FINALLY {
        EXPECT_GT(results[0].heal, 0);
    }
}

SINGLE_BATTLE_TEST("Non-Grass Bloom traps the user (prevents switching)")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET); // non-Grass
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BLOOM); }
        TURN { MOVE(opponent, MOVE_TELEPORT); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLOOM, player);
        // The opponent's teleport should fail if it tried to escape a trapped mon
    } FINALLY {
        // Ensure the player's Blooming volatile is set after the move
        ASSERT_TRUE(gBattleMons[PLAYER_ALIVE_BATTLER].volatiles.blooming);
    }
}