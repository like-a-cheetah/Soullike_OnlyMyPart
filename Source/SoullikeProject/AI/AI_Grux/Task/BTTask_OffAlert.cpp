// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Grux/Task/BTTask_OffAlert.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Interface/AIInterface.h"
#include "../EnemyAI.h"

UBTTask_OffAlert::UBTTask_OffAlert()
{
}

EBTNodeResult::Type UBTTask_OffAlert::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	if (AIPawn->GetIsAlert())
	{
		AIPawn->OffAlertMovement();

		FTimerHandle SetWalkableTimer;
		FSetAlertFinished SetAlertFinished;
		SetAlertFinished.BindLambda(
			[&]()
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_ISALERT, false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_GOHOME, true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		);
//		GetWorld()->GetTimerManager().SetTimer(SetWalkableTimer, SetAlertFinished, 1.5f, false);
	}

	return EBTNodeResult::InProgress;
}