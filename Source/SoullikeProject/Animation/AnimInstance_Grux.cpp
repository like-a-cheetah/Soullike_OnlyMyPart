// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimInstance_Grux.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"

#include "Interface/AIInterface.h"

UAnimInstance_Grux::UAnimInstance_Grux()
{
	MovingThreshould = 3.0f;
	JumpingThreshould = 100.0f;
}

void UAnimInstance_Grux::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UAnimInstance_Grux::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		//Rotation = CalculateDirection(Velocity, GetOwningActor()->GetActorRotation());
		GroundSpeed = Velocity.Size2D();
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould);

		IAIInterface* PawnAI = Cast<IAIInterface>(GetOwningActor());
		if (PawnAI)
		{
			bIsAlert = PawnAI->GetIsAlert();
			LookRotation = PawnAI->GetLookRotation();
		}
	}
}

void UAnimInstance_Grux::SetMovementMode(EMovementMode Mode)
{
}
