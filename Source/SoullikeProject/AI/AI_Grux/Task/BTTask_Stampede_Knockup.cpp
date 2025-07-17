// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Grux/Task/BTTask_Stampede_Knockup.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Character/Enemy.h"
#include "../EnemyAI.h"

UBTTask_Stampede_Knockup::UBTTask_Stampede_Knockup()
{
}

EBTNodeResult::Type UBTTask_Stampede_Knockup::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = EBTNodeResult::Type();

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

	AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (nullptr == Player)
	{
		return EBTNodeResult::Failed;
	}

	FAICharacterAttackFinished OnAttackFinished;
	OnAttackFinished.BindLambda(
		[&]()
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	);
	AIPawn->SetAIAttackDelegate(OnAttackFinished);

	Cast<AEnemy>(ControllingPawn)->Stampede_Knockup(Player->GetActorLocation());

	OwnerComp.GetBlackboardComponent()->SetValueAsInt(BBKEY_RANDOM, 50);

	return EBTNodeResult::InProgress;
}
