// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Grux/Service/BTService_Rotation.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "../EnemyAI.h"

UBTService_Rotation::UBTService_Rotation()
{
	NodeName = TEXT("Rotation");
	Interval = 0.1f;
}

void UBTService_Rotation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return;
	}

	FVector Center = ControllingPawn->GetActorLocation();
	UWorld* World = ControllingPawn->GetWorld();
	if (nullptr == World)
	{
		return;
	}
	
	UObject* Player = OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET);
	if (Player == nullptr)
	{
		return;
	}
	FVector Start = ControllingPawn->GetActorLocation();
	Start = { Start.X, Start.Y, 0 };
	FVector End = Cast<AActor>(Player)->GetActorLocation();
	End = { End.X, End.Y, 0 };

	FRotator ToPlayerRot = UKismetMathLibrary::FindLookAtRotation(Start, End);

	ControllingPawn->SetActorRotation(ToPlayerRot);	//lerp 방식으로 바꾸기
}
