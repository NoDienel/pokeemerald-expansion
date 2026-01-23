#include "global.h"
#include "test/battle/battle_test.h"

SINGLE_BATTLE_TEST("Petal Skating raises Speed by 2 when Blooming starts")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_BLOOM) == EFFECT_BLOOM);
        PLAYER(SPECIES_LILLIGANT) { Moves(MOVE_BLOOM); Ability(ABILITY_PETAL_SKATING); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_BLOOM); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLOOM, player);
        ANIMATION(ANIM_TYPE_STAT_CHANGE, ANIM_STAT_SPEED, player);
        MESSAGE("Lilligant's Speed rose sharply!");
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE + 2);
        EXPECT_TRUE(gBattleMons[PLAYER_ALIVE_BATTLER].volatiles.blooming);
    }
}

SINGLE_BATTLE_TEST("Petal Skating does not raise Speed above max stage")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_BLOOM) == EFFECT_BLOOM);
        PLAYER(SPECIES_LILLIGANT) { Moves(MOVE_BLOOM); Ability(ABILITY_PETAL_SKATING); Stats(HP(100), ATK(100), DEF(100), SPATK(100), SPDEF(100), SPE(100)); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_BLOOM); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLOOM, player);
    } THEN {
        // Max stat stage is 12, so this should be capped at 12
        EXPECT_LEQ(player->statStages[STAT_SPEED], MAX_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Petal Skating does not activate if already Blooming")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_BLOOM) == EFFECT_BLOOM);
        PLAYER(SPECIES_LILLIGANT) { Moves(MOVE_BLOOM); Ability(ABILITY_PETAL_SKATING); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_BLOOM); }
        TURN { MOVE(player, MOVE_BLOOM); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLOOM, player);
        ANIMATION(ANIM_TYPE_STAT_CHANGE, ANIM_STAT_SPEED, player);
        MESSAGE("Lilligant's Speed rose sharply!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLOOM, player);
    } THEN {
        // Should only have +2 Speed from the first Bloom, not +4
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE + 2);
    }
}
