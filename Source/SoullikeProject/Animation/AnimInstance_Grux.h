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

	virtual void NativeInitializeAnimation() override;	//�ִϸ��̼��� ó�� ������ ��

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;	//�ִϸ��̼��� ������Ʈ �� ��

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
	uint8 bIsIdle : 1;*/	////Idle�������� Ȯ���ϴ� bool

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 bIsJumping : 1;	//Jump �������� Ȯ���ϴ� bool

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float MovingThreshould;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 bIsFalling : 1;	//�������� ������ üũ(bool����)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 JumpingThreshould : 1;	//���������� üũ
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	uint8 bIsAlert : 1;	//�����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float LookRotation;	//���� �ٶ󺸴� ����

};
