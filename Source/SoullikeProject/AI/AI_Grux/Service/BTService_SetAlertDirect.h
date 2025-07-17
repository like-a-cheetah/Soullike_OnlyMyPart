// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SetAlertDirect.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EDirect : uint8
{
	Stop UMETA(DisplayName = "Stop"),
	Forward UMETA(DisplayName = "Forward"),
	Backward UMETA(DisplayName = "Backward"),
	Right UMETA(DisplayName = "Right"),
	Left UMETA(DisplayName = "Left"),
};

UCLASS()
class SOULLIKEPROJECT_API UBTService_SetAlertDirect : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_SetAlertDirect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
