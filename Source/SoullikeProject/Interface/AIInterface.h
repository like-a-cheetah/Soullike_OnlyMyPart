// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAIInterface : public UInterface
{
	GENERATED_BODY()
};

DECLARE_DELEGATE(FAICharacterAttackFinished);

/**
 * 
 */
class SOULLIKEPROJECT_API IAIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float GetAIPatrolRadius() = 0;
	virtual float GetAIDetectRange() = 0;
	virtual float GetAIAttackRange() = 0;
	virtual float GetAITurnSpeed() = 0;

	virtual void SetVelocity(float Speed) = 0;
	virtual void SetbOrientRotationToMovement(bool val) = 0;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) = 0;
	virtual void AttackByAI(int MontageNum) = 0;

	virtual void OffAlertMovement() = 0;
	virtual void OnAlertMovement() = 0;
	virtual bool GetIsAlert() const = 0;	//애니메이션 인터페이스에서 사용해야할듯

	virtual void SetLookRotation(float Rotation) = 0;
	virtual float GetLookRotation() = 0;

protected:
	uint8 bIsAlert : 1;

	float LookRotation;
};
