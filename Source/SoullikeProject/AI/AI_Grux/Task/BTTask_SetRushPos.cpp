// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Grux/Task/BTTask_SetRushPos.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "../EnemyAI.h"

UBTTask_SetRushPos::UBTTask_SetRushPos()
{
}

EBTNodeResult::Type UBTTask_SetRushPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (Target == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	if (ControllingPawn->GetDistanceTo(Target) <= 500.0f)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(BBKEY_RANDOM, 50);
		return EBTNodeResult::Failed;
	}

	//OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_RUSHPOS, Target->GetActorLocation());
	//한번 돌진하고서는 그냥 MoveTo로 하게끔
	OwnerComp.GetBlackboardComponent()->SetValueAsInt(BBKEY_RANDOM, 50);

	return EBTNodeResult::Succeeded;
}
