// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Grux/Task/BTTask_Alert.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Interface/AIInterface.h"
#include "../EnemyAI.h"

UBTTask_Alert::UBTTask_Alert()
{
	bNotifyTick = true;	//틱 단위로 실행하기 위해 설정하는 변수
}

EBTNodeResult::Type UBTTask_Alert::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::InProgress;
}

void UBTTask_Alert::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)	//task내에서 틱마다 실행되는 함수
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return;
	}

	IAIInterface* AIPawn = Cast<IAIInterface>(ControllingPawn);
	if (nullptr == AIPawn) {
		return;
	}

	AIPawn->SetVelocity(100.0f);

	switch(OwnerComp.GetBlackboardComponent()->GetValueAsEnum(BBKEY_ALERTDIRECT))
	{
	case 0:
		break;
	case 1:
		ControllingPawn->AddMovementInput(ControllingPawn->GetActorForwardVector());
		break;
	case 2:
		ControllingPawn->AddMovementInput(ControllingPawn->GetActorRightVector());
		break;
	case 3:
		ControllingPawn->AddMovementInput(ControllingPawn->GetActorRightVector() * -1.0f);
	}
}
