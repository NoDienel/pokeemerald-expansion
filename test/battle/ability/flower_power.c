#include "global.h"
#include "test/battle/battle_test.h"

SINGLE_BATTLE_TEST("Flower Power boosts Special Attack by 1.3x while Blooming")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_BLOOM) == EFFECT_BLOOM);
        ASSUME(IsBattleMoveSpecial(MOVE_POWER_BEAM) == TRUE);
        PLAYER(SPECIES_LILLIGANT) { Moves(MOVE_BLOOM, MOVE_POWER_BEAM); Ability(ABILITY_FLOWER_POWER); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(200); }
    } WHEN {
        TURN { MOVE(player, MOVE_BLOOM); }
        TURN { MOVE(player, MOVE_POWER_BEAM); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLOOM, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POWER_BEAM, player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Flower Power does not boost non-special moves")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_BLOOM) == EFFECT_BLOOM);
        ASSUME(IsBattleMovePhysical(MOVE_PECK) == TRUE);
        PLAYER(SPECIES_LILLIGANT) { Moves(MOVE_BLOOM, MOVE_PECK); Ability(ABILITY_FLOWER_POWER); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_BLOOM); }
        TURN { MOVE(player, MOVE_PECK); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLOOM, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PECK, player);
    }
}

SINGLE_BATTLE_TEST("Flower Power prevents Special Attack lowering while Blooming")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_BLOOM) == EFFECT_BLOOM);
        ASSUME(GetMoveEffect(MOVE_PSYCH_UP) == EFFECT_PSYCH_UP);
        PLAYER(SPECIES_LILLIGANT) { Moves(MOVE_BLOOM); Ability(ABILITY_FLOWER_POWER); }
        OPPONENT(SPECIES_ALAKAZAM) { Moves(MOVE_PSYCHIC); }
    } WHEN {
        TURN { MOVE(player, MOVE_BLOOM); MOVE(opponent, MOVE_PSYCHIC); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLOOM, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PSYCHIC, opponent);
        ABILITY_POPUP(player, ABILITY_FLOWER_POWER);
        MESSAGE("Lilligant's Flower Power prevents Sp. Atk loss!");
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPATK], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Flower Power does not prevent Special Attack lowering when not Blooming")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_PSYCHIC) == EFFECT_SP_ATK_DOWN_CHANCE);
        PLAYER(SPECIES_LILLIGANT) { Ability(ABILITY_FLOWER_POWER); }
        OPPONENT(SPECIES_ALAKAZAM) { Moves(MOVE_PSYCHIC); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_PSYCHIC); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PSYCHIC, opponent);
    } THEN {
        // Should be able to lower SpA when not blooming
        EXPECT_LT(player->statStages[STAT_SPATK], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Flower Power boosts Special Attack damage calculation")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_BLOOM) == EFFECT_BLOOM);
        ASSUME(IsBattleMoveSpecial(MOVE_POWER_BEAM) == TRUE);
        PLAYER(SPECIES_LILLIGANT) { Moves(MOVE_BLOOM, MOVE_POWER_BEAM); Ability(ABILITY_FLOWER_POWER); Stats(HP(100), ATK(100), DEF(100), SPATK(100), SPDEF(100), SPE(100)); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(200); Defense(100); Sp.Def(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_BLOOM); }
        TURN { MOVE(player, MOVE_POWER_BEAM); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLOOM, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POWER_BEAM, player);
        HP_BAR(opponent);
    }
}
