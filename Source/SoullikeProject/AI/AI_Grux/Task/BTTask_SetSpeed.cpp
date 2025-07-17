// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Grux/Task/BTTask_SetSpeed.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Interface/AIInterface.h"

UBTTask_SetSpeed::UBTTask_SetSpeed()
{
}

EBTNodeResult::Type UBTTask_SetSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	IAIInterface* AIPawn = Cast<IAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	AIPawn->SetVelocity(Speed);
	UE_LOG(LogTemp, Log, TEXT("succeeded"));


	return EBTNodeResult::Succeeded;
}
