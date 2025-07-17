// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Grux/Task/BTTask_LookAround.h"

#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Interface/AIInterface.h"
#include "../EnemyAI.h"

UBTTask_LookAround::UBTTask_LookAround()
{
	bNotifyTick = true;	//틱 단위로 실행하기 위해 설정하는 변수
}

EBTNodeResult::Type UBTTask_LookAround::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	AIPawn = Cast<IAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (nullptr == BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	Rotation = 0.0f;
	AIPawn->SetLookRotation(Rotation);
	//OwnerComp.GetAIOwner()->SetControlRotation(FRotator::ZeroRotator);
	Direct = EYourEnumType::Left;

	CurrentDelayTime = 0.0f;

	FTimerHandle InitRotateHandle;
	GetWorld()->GetTimerManager().SetTimer(InitRotateHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			AIPawn->SetLookRotation(0.0f);
		}
	), 10.0f, false);

	return EBTNodeResult::InProgress;
}

void UBTTask_LookAround::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)	//task내에서 틱마다 실행되는 함수
{
	switch (Direct)
	{
	case EYourEnumType::Left:
		Rotation = FMath::Lerp(Rotation, -90.0f, DeltaSeconds * 2.5f);

		if (Rotation <= -89.0f)
		{
			Direct = EYourEnumType::Right;
		}
		break;
	case EYourEnumType::Right:
		Rotation = FMath::Lerp(Rotation, 90.0f, DeltaSeconds * 2.5f);

		if (Rotation >= 89.0f)
		{
			Direct = EYourEnumType::Front;
		}
		break;
	case EYourEnumType::Front:
		Rotation = FMath::Lerp(Rotation, 0.0f, DeltaSeconds * 5.0f);

		CurrentDelayTime += DeltaSeconds;
		if (CurrentDelayTime >= DelayTime)
		{
			OwnerComp.GetAIOwner()->SetControlRotation(FRotator::ZeroRotator);
			AIPawn->SetLookRotation(0.0f);

			BlackboardComp->SetValueAsBool(BBKEY_ISRESETHOME, true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		break;
	}
	//OwnerComp.GetAIOwner()->SetControlRotation(FRotator(0.0f, Rotation, 0.0f));

	/*FVector temp;
	FRotator Temp;
	ControllingPawn->GetActorEyesViewPoint(temp, Temp);

	UE_LOG(LogTemp, Log, TEXT("%f %f %f"), Temp.Roll, Temp.Pitch, Temp.Yaw);*/

	AIPawn->SetLookRotation(Rotation);
}

EBTNodeResult::Type UBTTask_LookAround::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::AbortTask(OwnerComp, NodeMemory);

	AIPawn->SetLookRotation(0.0f);

	return EBTNodeResult::Aborted;
}
