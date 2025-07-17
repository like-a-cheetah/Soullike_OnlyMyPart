// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_RushTo.generated.h"

/**
 *
 */
UCLASS()
class SOULLIKEPROJECT_API UBTTask_RushTo : public UBTTask_MoveTo	//기본 MoveToTask 상속
{
	GENERATED_BODY()

public:
	UBTTask_RushTo();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	APawn* ControllingPawn;
	//IAIInterface* AIPawn;
	AActor* Player;

	float RushTime = 0.0f;
};
