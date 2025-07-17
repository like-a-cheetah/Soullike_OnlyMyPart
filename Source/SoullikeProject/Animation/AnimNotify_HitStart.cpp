// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_HitStart.h"

#include "Interface/AnimationAttackInterface.h"

void UAnimNotify_HitStart::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		IAnimationAttackInterface* AttackPawn = Cast<IAnimationAttackInterface>(MeshComp->GetOwner());
		if (AttackPawn)
		{
			AttackPawn->HitStart();
		}
	}
}
