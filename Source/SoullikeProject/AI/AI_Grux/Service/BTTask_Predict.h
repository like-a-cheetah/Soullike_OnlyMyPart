// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Predict.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UBTTask_Predict : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Predict();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
