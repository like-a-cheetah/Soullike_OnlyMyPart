// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstance_Grux.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UAnimInstance_Grux : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	UAnimInstance_Grux();

	bool GetIsFallin() { return bIsFalling; }

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetMovementMode(EMovementMode Mode);

protected:

	virtual void NativeInitializeAnimation() override;	//애니메이션이 처음 시작할 때

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;	//애니메이션이 업데이트 될 때

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
	TObjectPtr<class ACharacter> Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category = "Character")
	TObjectPtr<class UCharacterMovementComponent> Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float Rotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float GroundSpeed;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	uint8 bIsIdle : 1;*/	////Idle상태인지 확인하는 bool

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 bIsJumping : 1;	//Jump 상태인지 확인하는 bool

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float MovingThreshould;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 bIsFalling : 1;	//떨어지는 중인지 체크(bool형임)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 JumpingThreshould : 1;	//점프중인지 체크
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 bIsAlert : 1;	//경계모드

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float LookRotation;	//서서 바라보는 방향

};
