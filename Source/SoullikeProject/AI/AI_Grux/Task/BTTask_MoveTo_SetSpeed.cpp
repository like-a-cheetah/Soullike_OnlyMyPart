// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Grux/Task/BTTask_MoveTo_SetSpeed.h"

#include "AIController.h"

#include "Interface/AIInterface.h"

UBTTask_MoveTo_SetSpeed::UBTTask_MoveTo_SetSpeed()
{
}

EBTNodeResult::Type UBTTask_MoveTo_SetSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	if (Speed == 0.0f)
		UE_LOG(LogTemp, Log, TEXT("태스크에서 설정하는 속도가 0임"));
	AIPawn->SetVelocity(Speed);
	AIPawn->SetbOrientRotationToMovement(true);

	return EBTNodeResult::InProgress;
}
