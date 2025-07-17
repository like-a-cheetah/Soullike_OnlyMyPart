// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_AlertRange.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UBTService_AlertRange : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_AlertRange();

	UPROPERTY(Category = Node, EditAnyWhere, BlueprintReadWrite)
	float Range;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
private:
	const float AlertMaintainTime = 4.0f;
};
