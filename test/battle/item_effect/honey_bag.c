#include "global.h"
#include "test/battle.h"

DOUBLE_BATTLE_TEST("Using Honey from bag heals 25% of target's max HP")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { MaxHP(100); HP(50); }
        OPPONENT(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WOBBUFFET) { MaxHP(100); HP(100); Item(ITEM_HONEY); }
    } WHEN {
        TURN { USE_ITEM(playerRight, ITEM_HONEY, partyIndex: 0); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_ITEM_EFFECT, playerRight);
        HP_BAR(playerLeft, damage: -25);
    }
}

DOUBLE_BATTLE_TEST("Using Honey from bag caps at max HP")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { MaxHP(100); HP(90); }
        OPPONENT(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WOBBUFFET) { MaxHP(100); HP(100); Item(ITEM_HONEY); }
    } WHEN {
        TURN { USE_ITEM(playerRight, ITEM_HONEY, partyIndex: 0); }
    } SCENE {
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_ITEM_EFFECT, playerRight);
        HP_BAR(playerLeft); // should not exceed max
    }
}

DOUBLE_BATTLE_TEST("Ripen does not double Honey's effect when used from bag")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { MaxHP(100); HP(50); }
        OPPONENT(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_POLTCHAGEIST) { Ability(ABILITY_RIPEN); Item(ITEM_HONEY); }
    } WHEN {
        TURN { USE_ITEM(playerRight, ITEM_HONEY, partyIndex: 0); }
    } SCENE {
        // Honey should heal 25, not 50
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_ITEM_EFFECT, playerRight);
        HP_BAR(playerLeft, damage: -25);
    }
}