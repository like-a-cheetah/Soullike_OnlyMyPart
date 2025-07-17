// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_LookAround.generated.h"

/**
 * 
 */
enum class EYourEnumType : uint8
{
	Front = 0 UMETA(DisplayName = "Option 1"),
	Left UMETA(DisplayName = "Option 2"),
	Right UMETA(DisplayName = "Option 3")
};

UCLASS()
class SOULLIKEPROJECT_API UBTTask_LookAround : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_LookAround();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	APawn* ControllingPawn;
	class IAIInterface* AIPawn;
	class UAIPerceptionComponent* PerceptionComp;
	class UBlackboardComponent* BlackboardComp;

	float StartPerceptionYaw;
	float TargetPerceptionYaw;

	float Rotation;
	float PerceptionYaw;

	EYourEnumType Direct;

	const float DelayTime = 3.0f;
	float CurrentDelayTime;
};
