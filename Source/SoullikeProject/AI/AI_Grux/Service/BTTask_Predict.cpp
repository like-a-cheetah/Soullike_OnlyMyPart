// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Grux/Service/BTTask_Predict.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

#include "../EnemyAI.h"


UBTTask_Predict::UBTTask_Predict()
{
}

EBTNodeResult::Type UBTTask_Predict::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UWorld* World = OwnerComp.GetOwner()->GetWorld();
	if (!World)
	{
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
	if (NavSys)
	{
		FNavLocation NavLocation;
		if (NavSys->GetRandomReachablePointInRadius(OwnerComp.GetOwner()->GetActorLocation(), 1000.0f, NavLocation))
		{
			UE_LOG(LogTemp, Log, TEXT("%f %f %f"), NavLocation.Location.X, NavLocation.Location.Y, NavLocation.Location.Z);
			OwnerComp.GetBlackboardComponent()->SetValueAsVector((BBKEY_STIMULUSPOS), NavLocation.Location);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
