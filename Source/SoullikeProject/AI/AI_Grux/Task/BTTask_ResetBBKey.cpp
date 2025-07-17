// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Grux/Task/BTTask_ResetBBKey.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "../EnemyAI.h"

UBTTask_ResetBBKey::UBTTask_ResetBBKey()
{
}

EBTNodeResult::Type UBTTask_ResetBBKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->ClearValue(ResetKeyName);
	UE_LOG(LogTemp, Log, TEXT("%f"), OwnerComp.GetBlackboardComponent()->GetValueAsVector(ResetKeyName).X);

	return EBTNodeResult::Succeeded;
}
