// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Grux/Service/BTService_AlertRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "../EnemyAI.h"

UBTService_AlertRange::UBTService_AlertRange()
{
	NodeName = TEXT("AlertRange");
	Interval = 0.5f;
}

void UBTService_AlertRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
	if (DistanceToTarget <= Range)
	{
		Range = 1000.0f;
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_INALERTRANGE, true);
	}
	else
	{
		Range = 500.0f;
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_INALERTRANGE, false);
	}
}
