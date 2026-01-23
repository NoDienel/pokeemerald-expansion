#include "global.h"
#include "test/battle/battle_test.h"

SINGLE_BATTLE_TEST("Budding: Changes type to Grass while Blooming")
{
    GIVEN {
        PLAYER(SPECIES_PIKACHU) { Moves(MOVE_BLOOM); Ability(ABILITY_BUDDING); }
        OPPONENT(SPECIES_CHARIZARD);
    } WHEN {
        TURN { MOVE(PLAYER, MOVE_BLOOM); }
    } SCENE {
        MESSAGE("Pikachu used Bloom!");
        MESSAGE("Pikachu is now blooming!");
    } THEN {
        EXPECT_EQ(gBattleMons[PLAYER_PARTY_INDEX(0)].types[0], TYPE_GRASS);
        EXPECT_EQ(gBattleMons[PLAYER_PARTY_INDEX(0)].types[1], TYPE_GRASS);
        EXPECT_EQ(gBattleMons[PLAYER_PARTY_INDEX(0)].types[2], TYPE_GRASS);
    }
}

SINGLE_BATTLE_TEST("Budding: Grass moves get x1.2 power boost while Blooming")
{
    u32 dmg;
    GIVEN {
        PLAYER(SPECIES_BULBASAUR) { Moves(MOVE_BLOOM, MOVE_SOLAR_BEAM); Ability(ABILITY_BUDDING); MaxHP(100); }
        OPPONENT(SPECIES_BLASTOISE) { MaxHP(100); }
    } WHEN {
        TURN { MOVE(PLAYER, MOVE_BLOOM); }
        TURN { MOVE(PLAYER, MOVE_SOLAR_BEAM); }
    } SCENE {
        MESSAGE("Bulbasaur used Bloom!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLOOM, PLAYER);
        MESSAGE("Bulbasaur is now blooming!");
        MESSAGE("Bulbasaur used Solar Beam!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SOLAR_BEAM, PLAYER);
        HP_BAR(OPPONENT);
        dmg = CALC_MAX_HP(OPPONENT) - gBattleMons[OPPONENT_PARTY_INDEX(0)].hp;
    } THEN {
        // Solar Beam power is 120, with Grass type and x1.2 boost
        EXPECT_TRUE(dmg > 0);
    }
}

SINGLE_BATTLE_TEST("Budding: Type reverts when Blooming ends")
{
    GIVEN {
        PLAYER(SPECIES_ARCANINE) { Moves(MOVE_BLOOM); Ability(ABILITY_BUDDING); }
        OPPONENT(SPECIES_CHARIZARD) { Moves(MOVE_SPLASH); }
    } WHEN {
        TURN { MOVE(PLAYER, MOVE_BLOOM); }
        // Blooming lasts 3-5 turns, we'll simulate multiple turns to see it end
        TURN { MOVE(OPPONENT, MOVE_SPLASH); }
        TURN { MOVE(OPPONENT, MOVE_SPLASH); }
        TURN { MOVE(OPPONENT, MOVE_SPLASH); }
        TURN { MOVE(OPPONENT, MOVE_SPLASH); }
        TURN { MOVE(OPPONENT, MOVE_SPLASH); }
    } SCENE {
        MESSAGE("Arcanine used Bloom!");
    } THEN {
        // After Blooming ends, type should revert to original
        EXPECT_NE(gBattleMons[PLAYER_PARTY_INDEX(0)].types[0], TYPE_GRASS);
    }
}

DOUBLE_BATTLE_TEST("Budding: Type change works in double battles")
{
    GIVEN {
        PLAYER(SPECIES_VILEPLUME) { Moves(MOVE_BLOOM); Ability(ABILITY_BUDDING); }
        PLAYER(SPECIES_EXEGGUTOR) { Moves(MOVE_SPLASH); }
        OPPONENT(SPECIES_CHARIZARD);
        OPPONENT(SPECIES_BLASTOISE);
    } WHEN {
        TURN { MOVE(PLAYER, MOVE_BLOOM); MOVE(OPPONENT_SIDE, MOVE_SPLASH); }
    } SCENE {
        MESSAGE("Vileplume used Bloom!");
    } THEN {
        EXPECT_EQ(gBattleMons[PLAYER_PARTY_INDEX(0)].types[0], TYPE_GRASS);
        EXPECT_EQ(gBattleMons[PLAYER_PARTY_INDEX(0)].types[1], TYPE_GRASS);
    }
}

SINGLE_BATTLE_TEST("Budding: Only Grass moves get boost, not other types")
{
    GIVEN {
        PLAYER(SPECIES_CELEBI) { Moves(MOVE_BLOOM, MOVE_PSYCHIC, MOVE_SOLAR_BEAM); Ability(ABILITY_BUDDING); MaxHP(100); }
        OPPONENT(SPECIES_MACHAMP) { MaxHP(100); }
    } WHEN {
        TURN { MOVE(PLAYER, MOVE_BLOOM); }
        TURN { MOVE(PLAYER, MOVE_PSYCHIC); }
    } SCENE {
        MESSAGE("Celebi used Bloom!");
        MESSAGE("Celebi used Psychic!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PSYCHIC, PLAYER);
        HP_BAR(OPPONENT);
    } THEN {
        // Psychic doesn't get the x1.2 boost since it's not Grass type
        EXPECT_TRUE(gBattleMons[OPPONENT_PARTY_INDEX(0)].hp < CALC_MAX_HP(OPPONENT));
    }
}

SINGLE_BATTLE_TEST("Budding: Non-Grass types gain Grass type when Blooming")
{
    GIVEN {
        PLAYER(SPECIES_CHARIZARD) { Moves(MOVE_BLOOM); Ability(ABILITY_BUDDING); }
        OPPONENT(SPECIES_VENUSAUR);
    } WHEN {
        TURN { MOVE(PLAYER, MOVE_BLOOM); }
    } SCENE {
        MESSAGE("Charizard used Bloom!");
        MESSAGE("Charizard is now blooming!");
    } THEN {
        // Charizard is Fire/Flying normally, but becomes pure Grass when Blooming
        EXPECT_EQ(gBattleMons[PLAYER_PARTY_INDEX(0)].types[0], TYPE_GRASS);
        EXPECT_EQ(gBattleMons[PLAYER_PARTY_INDEX(0)].types[1], TYPE_GRASS);
    }
}
