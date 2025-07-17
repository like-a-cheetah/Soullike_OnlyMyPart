// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Grux/Service/BTService_Random.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "../EnemyAI.h"

UBTService_Random::UBTService_Random()
{
	NodeName = TEXT("Random");
	Interval = 2.0f;
}

void UBTService_Random::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return;
	}

	int32 RandomInt = FMath::RandRange(1, 100);
	OwnerComp.GetBlackboardComponent()->SetValueAsInt(BBKEY_RANDOM, RandomInt);

	UE_LOG(LogTemp, Log, TEXT("%d"), RandomInt);
}
