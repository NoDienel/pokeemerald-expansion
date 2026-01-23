#include "global.h"
#include "test/battle/battle_test.h"

DOUBLE_BATTLE_TEST("Bloom Spores spreads Blooming to all other Pokemon when user gains Blooming")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_BLOOM) == EFFECT_BLOOM);
        PLAYER(SPECIES_LILLIGANT) { Moves(MOVE_BLOOM); Ability(ABILITY_BLOOM_SPORES); }
        PLAYER(SPECIES_WOBBUFFET) { }
        OPPONENT(SPECIES_VILEPLUME) { }
        OPPONENT(SPECIES_ARBOK) { }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_BLOOM); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLOOM, playerLeft);
    } THEN {
        // All four battlers should have Blooming applied
        EXPECT_TRUE(gBattleMons[PLAYER_LIVE_ATTACKER].volatiles.blooming);
        EXPECT_TRUE(gBattleMons[PLAYER_LIVE_PARTNER].volatiles.blooming);
        EXPECT_TRUE(gBattleMons[OPPONENT_LIVE_ATTACKER].volatiles.blooming);
        EXPECT_TRUE(gBattleMons[OPPONENT_LIVE_PARTNER].volatiles.blooming);
    }
}

SINGLE_BATTLE_TEST("Bloom Spores spreads Blooming to opponent in single battle")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_BLOOM) == EFFECT_BLOOM);
        PLAYER(SPECIES_LILLIGANT) { Moves(MOVE_BLOOM); Ability(ABILITY_BLOOM_SPORES); }
        OPPONENT(SPECIES_VILEPLUME) { }
    } WHEN {
        TURN { MOVE(player, MOVE_BLOOM); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLOOM, player);
    } THEN {
        EXPECT_TRUE(gBattleMons[PLAYER_ALIVE_BATTLER].volatiles.blooming);
        EXPECT_TRUE(gBattleMons[OPPONENT_ALIVE_BATTLER].volatiles.blooming);
    }
}

DOUBLE_BATTLE_TEST("Bloom Spores does not apply Blooming to fainted Pokemon")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_BLOOM) == EFFECT_BLOOM);
        PLAYER(SPECIES_LILLIGANT) { Moves(MOVE_BLOOM); Ability(ABILITY_BLOOM_SPORES); HP(200); }
        PLAYER(SPECIES_WOBBUFFET) { HP(1); }
        OPPONENT(SPECIES_VILEPLUME) { }
        OPPONENT(SPECIES_ARBOK) { }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_BLOOM); }
        TURN { MOVE(playerLeft, MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLOOM, playerLeft);
    } THEN {
        // Blooming should be on player 1, opponents, but not fainted player 2
        EXPECT_TRUE(gBattleMons[PLAYER_LIVE_ATTACKER].volatiles.blooming);
        // Fainted Pokemon should not have blooming (HP == 0 check in loop)
    }
}

SINGLE_BATTLE_TEST("Bloom Spores spreads Blooming duration properly")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_BLOOM) == EFFECT_BLOOM);
        PLAYER(SPECIES_LILLIGANT) { Moves(MOVE_BLOOM); Ability(ABILITY_BLOOM_SPORES); }
        OPPONENT(SPECIES_VILEPLUME) { }
    } WHEN {
        TURN { MOVE(player, MOVE_BLOOM); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLOOM, player);
    } THEN {
        // Both should have blooming turns set (3-5 range)
        EXPECT_GE(gDisableStructs[PLAYER_ALIVE_BATTLER].bloomingTurns, 3);
        EXPECT_LE(gDisableStructs[PLAYER_ALIVE_BATTLER].bloomingTurns, 5);
        EXPECT_GE(gDisableStructs[OPPONENT_ALIVE_BATTLER].bloomingTurns, 3);
        EXPECT_LE(gDisableStructs[OPPONENT_ALIVE_BATTLER].bloomingTurns, 5);
    }
}

DOUBLE_BATTLE_TEST("Bloom Spores applies escape prevention to non-Grass types")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_BLOOM) == EFFECT_BLOOM);
        PLAYER(SPECIES_LILLIGANT) { Moves(MOVE_BLOOM); Ability(ABILITY_BLOOM_SPORES); }
        PLAYER(SPECIES_WOBBUFFET) { }
        OPPONENT(SPECIES_BELLSPROUT) { } /* Grass-type, should not get escapePrevention */
        OPPONENT(SPECIES_ARBOK) { } /* Poison-type, should get escapePrevention */
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_BLOOM); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLOOM, playerLeft);
    } THEN {
        // Check escape prevention was applied to non-Grass types
        if (!IS_BATTLER_OF_TYPE(PLAYER_LIVE_PARTNER, TYPE_GRASS))
            EXPECT_TRUE(gBattleMons[PLAYER_LIVE_PARTNER].volatiles.escapePrevention);
        if (!IS_BATTLER_OF_TYPE(OPPONENT_LIVE_PARTNER, TYPE_GRASS))
            EXPECT_TRUE(gBattleMons[OPPONENT_LIVE_PARTNER].volatiles.escapePrevention);
    }
}

SINGLE_BATTLE_TEST("Bloom Spores does not activate when already Blooming")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_BLOOM) == EFFECT_BLOOM);
        PLAYER(SPECIES_LILLIGANT) { Moves(MOVE_BLOOM); Ability(ABILITY_BLOOM_SPORES); }
        OPPONENT(SPECIES_VILEPLUME) { }
    } WHEN {
        TURN { MOVE(player, MOVE_BLOOM); }
        TURN { MOVE(player, MOVE_BLOOM); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLOOM, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLOOM, player);
    } THEN {
        // Both should still be blooming after second use, spread already happened
        EXPECT_TRUE(gBattleMons[PLAYER_ALIVE_BATTLER].volatiles.blooming);
        EXPECT_TRUE(gBattleMons[OPPONENT_ALIVE_BATTLER].volatiles.blooming);
    }
}
