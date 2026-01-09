#include "global.h"
#include "test/battle.h"

DOUBLE_BATTLE_TEST("Honey held item restores 25% of ally's health on switch-in (<=50% only)")
{
    s16 health;

    PARAMETRIZE { health = 40; }
    PARAMETRIZE { health = 75; }

    GIVEN {
        ASSUME(gItemsInfo[ITEM_HONEY].holdEffect == HOLD_EFFECT_HONEY);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_HONEY); }
        PLAYER(SPECIES_WOBBUFFET) { HP(health); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } SCENE {
        if (health == 40) {
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, playerLeft);
            HP_BAR(playerRight, damage: -25);
        } else {
            NONE_OF {
                ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, playerLeft);
                HP_BAR(playerRight, damage: -25);
            }
        }
    }
}