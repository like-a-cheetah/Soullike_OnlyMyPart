// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetRushPos.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UBTTask_SetRushPos : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_SetRushPos();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
