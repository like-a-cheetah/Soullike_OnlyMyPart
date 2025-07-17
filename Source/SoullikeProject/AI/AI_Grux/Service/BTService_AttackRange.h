// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_AttackRange.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UBTService_AttackRange : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_AttackRange();

	UPROPERTY(Category = Node, EditAnyWhere, BlueprintReadWrite)	//나중엔 몬스터의 공격 사정거리로 설정하기
	float Range;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
