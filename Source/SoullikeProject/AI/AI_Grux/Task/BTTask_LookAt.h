// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_LookAt.generated.h"

/**
 *
 */
UCLASS()
class SOULLIKEPROJECT_API UBTTask_LookAt : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_LookAt();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	APawn* ControllingPawn;
	class IAIInterface* AIPawn;
	float LookAtYaw;
	float StartYaw;
};
