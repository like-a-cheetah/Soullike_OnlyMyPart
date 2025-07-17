// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

//#include "Perception/AISense_Prediction.h"

#include "EnemyAI.h"

#include "AIController_Monster.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EStimulus : uint8
{
	None = 0,
	Sight,
	Hearing
};

UCLASS()
class SOULLIKEPROJECT_API AAIController_Monster : public AAIController
{
	GENERATED_BODY()
	
public:
	AAIController_Monster();
	void RunAI();
	void StopAI();
	void Tick(float DeltaTime);
	void BeginPlay();

	class UAISense_Prediction* GetAISense_Prediction() { return AISense_Prediction; }

private:
	void SetupPerceptionSystem();
	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);

	void SetForget();

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;
	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;

private:
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UAISenseConfig_Sight* SightConfig;
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UAISenseConfig_Hearing* HearingConfig;
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UAISenseConfig_Prediction* PredictionConfig;

private:
	float PredictionTime = 5.0f;

	class UAISense_Prediction* AISense_Prediction;
};
