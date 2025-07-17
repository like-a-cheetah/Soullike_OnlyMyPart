// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Grux/Service/BTService_SetAlertDirect.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "../EnemyAI.h"

UBTService_SetAlertDirect::UBTService_SetAlertDirect()
{
	NodeName = TEXT("SetAlertDirect");
	Interval = 4.0f;
}

void UBTService_SetAlertDirect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return;
	}

	int Random = rand() % 4;
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(BBKEY_ALERTDIRECT, Random);
	//OwnerComp.GetBlackboardComponent()->SetValueAsEnum(BBKEY_TEMP, asdf);	////안되는 이유 모름
}
