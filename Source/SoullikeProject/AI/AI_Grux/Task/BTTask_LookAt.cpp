// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Grux/Task/BTTask_LookAt.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIController.h"

#include "../EnemyAI.h"
#include "Interface/AIInterface.h"

UBTTask_LookAt::UBTTask_LookAt()
{
	bNotifyTick = true;	//틱 단위로 실행하기 위해 설정하는 변수
}

EBTNodeResult::Type UBTTask_LookAt::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	AIPawn = Cast<IAIInterface>(ControllingPawn);
	if (AIPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	StartYaw = 0.0f;

	FVector OwnerPos = ControllingPawn->GetActorLocation();
	FVector StimulusPos = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_STIMULUSPOS);
	FRotator LookAtRot = UKismetMathLibrary::FindRelativeLookAtRotation(ControllingPawn->GetActorTransform(), StimulusPos);

	LookAtYaw = LookAtRot.Yaw;

	AIPawn->SetLookRotation(StartYaw);

	return EBTNodeResult::InProgress;
}

void UBTTask_LookAt::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	StartYaw = FMath::Lerp(StartYaw, LookAtYaw, DeltaSeconds * 2.5f);
	AIPawn->SetLookRotation(StartYaw);

	if (FMath::IsNearlyEqual(StartYaw, LookAtYaw, 0.01f))
	{
		AIPawn->SetLookRotation(0.0f);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

EBTNodeResult::Type UBTTask_LookAt::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::AbortTask(OwnerComp, NodeMemory);

	AIPawn->SetLookRotation(0.0f);

	return EBTNodeResult::Aborted;
}
