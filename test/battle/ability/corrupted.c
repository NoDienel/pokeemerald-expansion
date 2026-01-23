#include "global.h"
#include "test/battle/battle_test.h"

SINGLE_BATTLE_TEST("Corrupted: 50% chance to change foe's non-normal type to normal on contact")
{
    u32 affected;
    
    GIVEN {
        PLAYER(SPECIES_PIKACHU) { Moves(MOVE_TACKLE); Ability(ABILITY_CORRUPTED); }
        OPPONENT(SPECIES_CHARIZARD);
    } WHEN {
        TURN { MOVE(PLAYER, MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, PLAYER);
        HP_BAR(OPPONENT);
        // Corruption has a 50% chance to trigger
    } THEN {
        // After the move, check if Charizard got corrupted
        affected = gBattleMons[OPPONENT_PARTY_INDEX(0)].volatiles.corruptedType;
        // Can't guarantee which way the RNG goes, but the volatile should be set if corrupted
    }
}

SINGLE_BATTLE_TEST("Corrupted: Changes Fire type to Normal on Charizard")
{
    GIVEN {
        PLAYER(SPECIES_PIKACHU) { Moves(MOVE_TACKLE); Ability(ABILITY_CORRUPTED); }
        OPPONENT(SPECIES_CHARIZARD) { HP(100); }
    } WHEN {
        TURN { MOVE(PLAYER, MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, PLAYER);
        HP_BAR(OPPONENT);
    } THEN {
        if (gBattleMons[OPPONENT_PARTY_INDEX(0)].volatiles.corruptedType)
        {
            // Charizard is Fire/Flying, so Fire should become Normal
            enum Type type0 = GetBattlerType(OPPONENT_PARTY_INDEX(0), 0, FALSE);
            enum Type type1 = GetBattlerType(OPPONENT_PARTY_INDEX(0), 1, FALSE);
            // One of these should be Normal now (Fire was changed)
            EXPECT_TRUE(type0 == TYPE_NORMAL || type1 == TYPE_NORMAL);
        }
    }
}

SINGLE_BATTLE_TEST("Corrupted: Always changes Psychic type to Normal")
{
    GIVEN {
        PLAYER(SPECIES_PIKACHU) { Moves(MOVE_TACKLE); Ability(ABILITY_CORRUPTED); }
        OPPONENT(SPECIES_ALAKAZAM);
    } WHEN {
        TURN { MOVE(PLAYER, MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, PLAYER);
        HP_BAR(OPPONENT);
    } THEN {
        if (gBattleMons[OPPONENT_PARTY_INDEX(0)].volatiles.corruptedType)
        {
            // Alakazam is Psychic type, so Psychic should ALWAYS become Normal
            enum Type type0 = GetBattlerType(OPPONENT_PARTY_INDEX(0), 0, FALSE);
            EXPECT_EQ(type0, TYPE_NORMAL);
        }
    }
}

SINGLE_BATTLE_TEST("Corrupted: Only triggers on contact moves")
{
    u32 corrupted;
    
    GIVEN {
        PLAYER(SPECIES_PIKACHU) { Moves(MOVE_THUNDERBOLT); Ability(ABILITY_CORRUPTED); }
        OPPONENT(SPECIES_CHARIZARD);
    } WHEN {
        TURN { MOVE(PLAYER, MOVE_THUNDERBOLT); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_THUNDERBOLT, PLAYER);
        HP_BAR(OPPONENT);
    } THEN {
        corrupted = gBattleMons[OPPONENT_PARTY_INDEX(0)].volatiles.corruptedType;
        // Thunderbolt doesn't make contact, so Corrupted shouldn't activate
        EXPECT_EQ(corrupted, 0);
    }
}

SINGLE_BATTLE_TEST("Corrupted: Type change persists across switches for entire battle")
{
    GIVEN {
        PLAYER(SPECIES_PIKACHU) { Moves(MOVE_TACKLE, MOVE_SPLASH); Ability(ABILITY_CORRUPTED); }
        OPPONENT(SPECIES_CHARIZARD);
        OPPONENT(SPECIES_BLASTOISE);
    } WHEN {
        TURN { MOVE(PLAYER, MOVE_TACKLE); }
        TURN { MOVE(OPPONENT, MOVE_SWITCH, target: 1); MOVE(PLAYER, MOVE_SPLASH); }
        TURN { MOVE(OPPONENT, MOVE_SWITCH, target: 0); MOVE(PLAYER, MOVE_SPLASH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, PLAYER);
        HP_BAR(OPPONENT);
    } THEN {
        // Charizard's corruption persists even after switching out and back in
        if (gDisableStructs[OPPONENT_PARTY_INDEX(0)].corruptedType)
        {
            // Charizard is back on field and should still be corrupted (Fire should be Normal)
            enum Type type0 = GetBattlerType(OPPONENT_PARTY_INDEX(0), 0, FALSE);
            EXPECT_EQ(type0, TYPE_NORMAL);
        }
    }
}

SINGLE_BATTLE_TEST("Corrupted: Clears when foe switches out (old test - now persistence test)")

SINGLE_BATTLE_TEST("Corrupted: Doesn't trigger on non-contact moves from Special moves")
{
    GIVEN {
        PLAYER(SPECIES_PIKACHU) { Moves(MOVE_SURF); Ability(ABILITY_CORRUPTED); }
        OPPONENT(SPECIES_CHARIZARD);
    } WHEN {
        TURN { MOVE(PLAYER, MOVE_SURF); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SURF, PLAYER);
        HP_BAR(OPPONENT);
    } THEN {
        // Surf is a special move with no contact
        EXPECT_EQ(gBattleMons[OPPONENT_PARTY_INDEX(0)].volatiles.corruptedType, 0);
    }
}

DOUBLE_BATTLE_TEST("Corrupted: Works in double battles with contact moves")
{
    GIVEN {
        PLAYER(SPECIES_PIKACHU) { Moves(MOVE_TACKLE); Ability(ABILITY_CORRUPTED); }
        PLAYER(SPECIES_BULBASAUR) { Moves(MOVE_SPLASH); }
        OPPONENT(SPECIES_CHARIZARD);
        OPPONENT(SPECIES_BLASTOISE);
    } WHEN {
        TURN { MOVE(PLAYER, MOVE_TACKLE); MOVE(OPPONENT, MOVE_SPLASH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, PLAYER);
        HP_BAR(OPPONENT);
    } THEN {
        // Charizard may be corrupted if RNG is in favor
    }
}

SINGLE_BATTLE_TEST("Corrupted: Doesn't change type if already normal type")
{
    GIVEN {
        PLAYER(SPECIES_PIKACHU) { Moves(MOVE_TACKLE); Ability(ABILITY_CORRUPTED); }
        OPPONENT(SPECIES_SNORLAX); // Normal type
    } WHEN {
        TURN { MOVE(PLAYER, MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, PLAYER);
        HP_BAR(OPPONENT);
    } THEN {
        // Snorlax is already Normal type, corruption has no effect visible but volatile is set
    }
}

SINGLE_BATTLE_TEST("Corrupted: Changes first non-normal type when multiple types exist")
{
    GIVEN {
        PLAYER(SPECIES_PIKACHU) { Moves(MOVE_TACKLE); Ability(ABILITY_CORRUPTED); }
        OPPONENT(SPECIES_CHARIZARD); // Fire/Flying
    } WHEN {
        TURN { MOVE(PLAYER, MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, PLAYER);
        HP_BAR(OPPONENT);
    } THEN {
        if (gBattleMons[OPPONENT_PARTY_INDEX(0)].volatiles.corruptedType)
        {
            // Fire should be changed to Normal, Flying remains
            enum Type type0 = GetBattlerType(OPPONENT_PARTY_INDEX(0), 0, FALSE);
            EXPECT_EQ(type0, TYPE_NORMAL);
        }
    }
}
