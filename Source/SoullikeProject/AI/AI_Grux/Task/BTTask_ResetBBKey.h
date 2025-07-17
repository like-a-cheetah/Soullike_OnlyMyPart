// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ResetBBKey.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UBTTask_ResetBBKey : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_ResetBBKey();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

public:
	UPROPERTY(Category = Node, EditAnyWhere, BlueprintReadWrite)
	FName ResetKeyName;
};
