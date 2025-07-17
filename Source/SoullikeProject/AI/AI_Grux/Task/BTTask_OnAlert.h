// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_OnAlert.generated.h"

/**
 * 
 */

DECLARE_DELEGATE(FSetAlertFinished);

UCLASS()
class SOULLIKEPROJECT_API UBTTask_OnAlert : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_OnAlert();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
