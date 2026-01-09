#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(IsSoundMove(MOVE_SING) == TRUE);
    ASSUME(IsSoundMove(MOVE_SONIC_BOOM) == TRUE);
    ASSUME(GetMoveEffect(MOVE_SONIC_BOOM) == EFFECT_FIXED_HP_DAMAGE);
    ASSUME(GetMoveFixedHPDamage(MOVE_SONIC_BOOM) == 20);
}

SINGLE_BATTLE_TEST("Resonate bounces back status sound moves like Magic Bounce")
{
    GIVEN {
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_ESPEON) { Ability(ABILITY_RESONATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_SING); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_RESONATE);
        NOT ANIMATION(ANIM_TYPE_MOVE, MOVE_SING, player);
        MESSAGE("Wynaut's Sing was bounced back by the opposing Espeon's Resonate!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SING, opponent);
        STATUS_ICON(player, sleep: TRUE);
    }
}

SINGLE_BATTLE_TEST("Resonate returns 25% of damaging sound moves as typeless sound damage")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { MaxHP(100); HP(100); }
        OPPONENT(SPECIES_ALAKAZAM) { Ability(ABILITY_RESONATE); MaxHP(100); HP(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_SONIC_BOOM); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_RESONATE);
        NOT ANIMATION(ANIM_TYPE_MOVE, MOVE_SONIC_BOOM, player);
        MESSAGE("Wobbuffet's Sonic Boom was bounced back by the opposing Alakazam's Resonate!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SONIC_BOOM, opponent);
        HP_BAR(player, captureDamage: &results[0].damage);
    } FINALLY {
        EXPECT(results[0].damage == 5);
    }
}
