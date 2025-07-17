// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Rotation.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UBTService_Rotation : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_Rotation();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
};
