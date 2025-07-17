// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Grux/Service/BTService_AttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "../EnemyAI.h"

UBTService_AttackRange::UBTService_AttackRange()
{
	NodeName = TEXT("AttackRange");
	Interval = 0.001f;
}

void UBTService_AttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return;
	}

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (nullptr == Target)
	{
		return;
	}

	float DistanceToTarget = ControllingPawn->GetDistanceTo(Target);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_INATTACKRANGE, DistanceToTarget <= Range);
}
