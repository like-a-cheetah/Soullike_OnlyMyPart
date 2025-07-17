// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Interface/AnimationAttackInterface.h"
#include "Interface/CharacterWidgetInterface.h"
#include "Interface/AIInterface.h"

#include "Enemy.generated.h"

UCLASS()
class SOULLIKEPROJECT_API AEnemy : public ACharacter, public IAnimationAttackInterface, public ICharacterWidgetInterface, public IAIInterface
{
	GENERATED_BODY()

	public:
	// Sets default values for this character's properties
	AEnemy();

	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Combo Action Section
protected:

	void SetupRef();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TArray<TObjectPtr<class UAnimMontage>> AttackMontages;

	void ProcessComboCommand();

	void ComboActionBegin(int MontageNum);
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);
	virtual void AttackTaskEnd();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	UCapsuleComponent* LWeaponCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	UCapsuleComponent* RWeaponCollision;

	//Attack & Hit Section

	uint8 bIsAttack : 1;

protected:
	virtual void AttackHitCheck();
	virtual void HitStart();
	virtual void HitEnd();
public:
	UFUNCTION(BluePrintCallable)
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	UFUNCTION()
	void BeginOverlapLWeapon(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlapLWeapon(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
	UFUNCTION()
	void BeginOverlapRWeapon(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlapRWeapon(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
private:
	//FVector<AActor*> OverlapActors;
	uint8 bIsPlayerHitted : 1;	//b
	uint8 bHitCheck : 1;	//b

	//Dead Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAcess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAcess = "true"))
	TObjectPtr<class UAnimMontage> HittedMontage;

	virtual void SetDead();
	void PlayDeadAnimation();

	float DeadEventDelayTime = 5.0f;

	void DoDisappear();

private:
	TObjectPtr<APlayerController>* Player;

	//Stat Section
protected:

	// UI Widget Section

	virtual void SetupCharacterWidget(class UMyUserWidget* InUserWidget) override;

	//AI Section
protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void SetVelocity(float Speed) override;
	virtual void SetbOrientRotationToMovement(bool val) override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void AttackByAI(int MontageNum) override;

	virtual void OnAlertMovement() override;
	virtual void OffAlertMovement() override;	//임시

public:
	virtual bool GetIsAlert() const override { return bIsAlert; }

	void TimerSetMovementModeWalking();	//임시

	//스킬
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> Stampede_KnockupMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> StampedeMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> Ultimate_RoarMontage;

public:
	UFUNCTION(BluePrintCallable)
	void Stampede_Knockup(FVector TargetPos);

	void Stampede();

	FAICharacterAttackFinished OnAttackFinished;

protected:
	virtual void SetLookRotation(float Rotation) override;
	virtual float GetLookRotation() override { return LookRotation; }

protected:
	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;
};
