// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Grux/Task/BTTask_RushTo.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Interface/AIInterface.h"
#include "Character/Enemy.h"
#include "../EnemyAI.h"

UBTTask_RushTo::UBTTask_RushTo()
{
	bNotifyTick = true;	//틱 단위로 실행하기 위해 설정하는 변수
}

EBTNodeResult::Type UBTTask_RushTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	IAIInterface* AIPawn = Cast<IAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (Player == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	//OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_RUSHPOS, Player->GetActorLocation());

	Cast<AEnemy>(ControllingPawn)->Stampede();	//임시(캡슐화?)

	RushTime = 0.0f;

	return EBTNodeResult::InProgress;
}

void UBTTask_RushTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)	//task내에서 틱마다 실행되는 함수
{
	RushTime += DeltaSeconds;	//필요없을듯
	UE_LOG(LogTemp, Log, TEXT("%f"), RushTime);
	if (ControllingPawn->GetDistanceTo(Player) <= 400.0f || RushTime >= 2.0f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}