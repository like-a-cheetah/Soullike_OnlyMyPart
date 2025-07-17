// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveTo_SetSpeed.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UBTTask_MoveTo_SetSpeed : public UBTTask_MoveTo
{
	GENERATED_BODY()

public:
	UBTTask_MoveTo_SetSpeed();

	UPROPERTY(Category = Node, EditAnyWhere, BlueprintReadWrite)
	float Speed;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
