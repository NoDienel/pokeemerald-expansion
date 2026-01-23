#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Silly Rascal causes all battlers to skip their next turn with 50% chance")
{
    s32 turnTaken;
    PARAMETRIZE { turnTaken = 0; }  // Failed random check
    PARAMETRIZE { turnTaken = 1; }  // Successful random check

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_SILLY_RASCAL); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
        TURN {
            if (turnTaken == 0)
            {
                MOVE(player, MOVE_TACKLE);
                MOVE(opponent, MOVE_TACKLE);
            }
            else
            {
                // Both should skip their moves
            }
        }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, player);
        HP_BAR(opponent);
        if (turnTaken == 1)
        {
            // On the second turn, both should loaf around
            MESSAGE("Wobbuffet is loafing around!");
            MESSAGE("The opposing Wobbuffet is loafing around!");
        }
        else
        {
            // Both should move normally
            ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, player);
            ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, opponent);
        }
    }
}
