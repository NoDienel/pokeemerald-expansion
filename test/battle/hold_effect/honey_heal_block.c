#include "global.h"
#include "test/battle.h"

DOUBLE_BATTLE_TEST("Honey held item is blocked by Heal Block")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_HEAL_BLOCK) == EFFECT_HEAL_BLOCK);
        PLAYER(SPECIES_WOBBUFFET)
        PLAYER(SPECIES_WOBBUFFET) { HP(75); MaxHP(100); }
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_HONEY); }
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponentLeft, MOVE_HEAL_BLOCK, target: playerRight); }
        TURN { SWITCH(playerLeft, 2); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HEAL_BLOCK, opponentLeft);
        NONE_OF {
                ABILITY_POPUP(playerLeft, ABILITY_NONE);
                HP_BAR(playerRight, damage: -25);
            }
    }
}
