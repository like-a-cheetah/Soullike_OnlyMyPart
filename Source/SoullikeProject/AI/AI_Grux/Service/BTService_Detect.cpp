// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI_Grux/Service/BTService_Detect.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

#include "../EnemyAI.h"
#include "Interface/AIInterface.h"
//#include "Physics/Physics.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	IAIInterface* AIPawn = Cast<IAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return;
	}

	float DetectRadius = AIPawn->GetAIDetectRange();

//	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(SCENE_QUERY_STAT(Detect), false, ControllingPawn);
	//bool bResult = World->OverlapMultiByChannel(	//플레이어가 다수라고 가정해서 multi, 나중에 바꾸기
	//	OverlapResults,
	//	Center,
	//	FQuat::Identity,
	//	ECollision,
	//	FCollisionShape::MakeSphere(DetectRadius),
	//	CollisionQueryParam
	//);

	//if (bResult)
	//{
	//	for (auto const& OverlapResult : OverlapResults)
	//	{
	//		APawn* Pawn = Cast<APawn>(OverlapResult.GetActor());
	//		if (Pawn && Pawn->GetController()->IsPlayerController())
	//		{
	//			AIPawn->SetVelocity(600.0f);

	//			OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, Pawn);
	//			OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_RUSHPOS, Pawn->GetActorLocation());
	//			DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

	//			DrawDebugPoint(World, Pawn->GetActorLocation(), 10.0f, FColor::Green, false, 0.2f);
	//			DrawDebugLine(World, ControllingPawn->GetActorLocation(), Pawn->GetActorLocation(), FColor::Green, false, 0.27f);
	//			return;
	//		}
	//	}
	//}
	AIPawn->SetVelocity(300.0f);	//수정필요
	
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}
