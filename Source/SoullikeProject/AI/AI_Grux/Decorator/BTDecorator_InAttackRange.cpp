// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Grux/Decorator/BTDecorator_InAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Interface/AIInterface.h"
#include "../EnemyAI.h"


UBTDecorator_InAttackRange::UBTDecorator_InAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_InAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return false;
	}

	IAIInterface* AIPawn = Cast<IAIInterface>(ControllingPawn);
	if (nullptr == AIPawn) {
		return false;
	}

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (nullptr == Target)
	{
		return false;
	}

	float DistanceToTarget = ControllingPawn->GetDistanceTo(Target);
	float AttackRangeWithRadius = AIPawn->GetAIAttackRange();
	bResult = (DistanceToTarget <= AttackRangeWithRadius);
	return bResult;
}
