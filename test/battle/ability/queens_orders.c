#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(MOVE_ATTACK_ORDER != MOVE_NONE);
    ASSUME(MOVE_DEFEND_ORDER != MOVE_NONE);
    ASSUME(MOVE_HEAL_ORDER != MOVE_NONE);
}

DOUBLE_BATTLE_TEST("Queens Orders copies Attack Order and targets the same target")
{
    GIVEN {
        PLAYER(SPECIES_VESPIQUEN) { Ability(ABILITY_QUEENS_ORDERS); Speed(5); }
        PLAYER(SPECIES_VESPIQUEN) { Speed(10); Moves(MOVE_ATTACK_ORDER); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(2); }
    } WHEN {
        TURN { MOVE(playerRight, MOVE_ATTACK_ORDER, target: opponentLeft); }
    } SCENE {
        // playerRight's Attack Order hits opponentLeft
        HP_BAR(opponentLeft);
        // playerLeft (with Queens Orders) copies and hits the same target (opponentLeft)
        ABILITY_POPUP(playerLeft, ABILITY_QUEENS_ORDERS);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ATTACK_ORDER, playerLeft);
        HP_BAR(opponentLeft);
    }
}

DOUBLE_BATTLE_TEST("Queens Orders copies Defend Order and targets self")
{
    GIVEN {
        PLAYER(SPECIES_VESPIQUEN) { Ability(ABILITY_QUEENS_ORDERS); Speed(5); }
        PLAYER(SPECIES_VESPIQUEN) { Speed(10); Moves(MOVE_DEFEND_ORDER); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(2); }
    } WHEN {
        TURN { MOVE(playerRight, MOVE_DEFEND_ORDER); }
    } SCENE {
        // playerRight uses Defend Order
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DEFEND_ORDER, playerRight);
        // playerLeft (with Queens Orders) copies and targets itself
        ABILITY_POPUP(playerLeft, ABILITY_QUEENS_ORDERS);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DEFEND_ORDER, playerLeft);
    }
}

DOUBLE_BATTLE_TEST("Queens Orders copies Heal Order and targets self")
{
    GIVEN {
        PLAYER(SPECIES_VESPIQUEN) { Ability(ABILITY_QUEENS_ORDERS); Speed(5); MaxHP(100); CurrentHP(50); }
        PLAYER(SPECIES_VESPIQUEN) { Speed(10); MaxHP(100); CurrentHP(50); Moves(MOVE_HEAL_ORDER); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(2); }
    } WHEN {
        TURN { MOVE(playerRight, MOVE_HEAL_ORDER); }
    } SCENE {
        // playerRight uses Heal Order
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HEAL_ORDER, playerRight);
        HP_BAR(playerRight);
        // playerLeft (with Queens Orders) copies and targets itself
        ABILITY_POPUP(playerLeft, ABILITY_QUEENS_ORDERS);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HEAL_ORDER, playerLeft);
        HP_BAR(playerLeft);
    }
}

DOUBLE_BATTLE_TEST("Queens Orders only activates when an ally uses an Order move")
{
    GIVEN {
        PLAYER(SPECIES_VESPIQUEN) { Ability(ABILITY_QUEENS_ORDERS); Speed(5); }
        PLAYER(SPECIES_VESPIQUEN) { Speed(10); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(2); }
    } WHEN {
        TURN { MOVE(playerRight, MOVE_TACKLE, target: opponentLeft); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, playerRight);
        HP_BAR(opponentLeft);
        // Queens Orders should NOT activate for non-Order moves
        NOT ABILITY_POPUP(playerLeft, ABILITY_QUEENS_ORDERS);
    }
}