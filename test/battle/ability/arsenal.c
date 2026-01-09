#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(IsBallisticMove(MOVE_ELECTRO_BALL));
}

SINGLE_BATTLE_TEST("Arsenal bypasses Bulletproof and allows ballistic moves to hit")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ARSENAL); }
        OPPONENT(SPECIES_CHESPIN) { Ability(ABILITY_BULLETPROOF); }
    } WHEN {
        TURN { MOVE(player, MOVE_ELECTRO_BALL); }
    } SCENE {
        NONE_OF {
            ABILITY_POPUP(opponent, ABILITY_BULLETPROOF);
            MESSAGE("The opposing Chespin's Bulletproof blocks Electro Ball!");
        }
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ELECTRO_BALL, player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Arsenal boosts ballistic move power", s16 damage)
{
    u16 ability;
    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_ARSENAL; }

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_CHESPIN);
    } WHEN {
        TURN { MOVE(player, MOVE_ELECTRO_BALL); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5), results[1].damage);
    }
}