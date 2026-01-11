#include "global.h"
#include "battle.h"
#include "battle_ai_main.h"

const u8 *gAIScriptPtr = NULL;

void BattleAI_SetupItems(void)
{
    return;
}

void BattleAI_SetupFlags(void)
{
    return;
}

void BattleAI_SetupAIData(u8 defaultScoreMoves, u32 battler)
{
    (void)defaultScoreMoves;
    (void)battler;
}

void ComputeBattlerDecisions(u32 battler)
{
    if (gAiBattleData == NULL)
        return;

    if (battler < MAX_BATTLERS_COUNT)
    {
        if (gAiBattleData->chosenMoveIndex[battler] == 0xFFFFFFFF)
            gAiBattleData->chosenMoveIndex[battler] = 0;
        if (gAiBattleData->chosenTarget[battler] == 0xFF)
            gAiBattleData->chosenTarget[battler] = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
    }
}

u32 BattleAI_ChooseMoveIndex(u32 battler)
{
    if (gAiBattleData == NULL)
        return 0;

    return gAiBattleData->chosenMoveIndex[battler];
}

void Ai_InitPartyStruct(void)
{
    return;
}

void Ai_UpdateSwitchInData(u32 battler)
{
    (void)battler;
}

void Ai_UpdateFaintData(u32 battler)
{
    (void)battler;
}

void SetAiLogicDataForTurn(struct AiLogicData *aiData)
{
    if (gAiLogicData == NULL || aiData == NULL)
        return;

    memcpy(gAiLogicData, aiData, sizeof(*gAiLogicData));
}

void ResetDynamicAiFunc(void)
{
    return;
}

void AI_TrySwitchOrUseItem(u32 battler)
{
    (void)battler;
}

void SetBattlerAiData(u32 battlerId, struct AiLogicData *aiData)
{
    (void)battlerId;
    (void)aiData;
}
