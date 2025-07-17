#include "AI/AI_Grux/AIController_Monster.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Prediction.h"
#include "Perception/AISense_Prediction.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"

#include "EnemyAI.h"


AAIController_Monster::AAIController_Monster()
{
    static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Game/AI/BB_Enemy.BB_Enemy"));
    if (BBAssetRef.Object)
    {
        BBAsset = BBAssetRef.Object;
    }

    static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Game/AI/BT_Enemy.BT_Enemy"));
    if (BTAssetRef.Object)
    {
        BTAsset = BTAssetRef.Object;
    }

    SetupPerceptionSystem();
}

void AAIController_Monster::RunAI()
{
    UBlackboardComponent* BlackboardPtr = Blackboard.Get();
    if (UseBlackboard(BBAsset, BlackboardPtr))
    {
        Blackboard->SetValueAsVector(BBKEY_HOMEPOS, GetPawn()->GetActorLocation());
        Blackboard->SetValueAsInt(BBKEY_RANDOM, 0);

        bool RunResult = RunBehaviorTree(BTAsset);
        ensure(RunResult);
    }
}

void AAIController_Monster::StopAI()
{
    UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
    if (BTComponent)
    {
        BTComponent->StopTree();
    }
}

void AAIController_Monster::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    SetForget();
}

void AAIController_Monster::BeginPlay()
{
    Super::BeginPlay();

    if (Blackboard)
    {
        Blackboard->SetValueAsBool(BBKEY_ISRESETHOME, true);
    }
}

void AAIController_Monster::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    RunAI();
}

void AAIController_Monster::SetupPerceptionSystem()
{
    PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));
    SetPerceptionComponent(*PerceptionComponent);

    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
    if (SightConfig)
    {
        SightConfig->SightRadius = 5500.F;
        SightConfig->LoseSightRadius = SightConfig->SightRadius + 500.F;
        SightConfig->PeripheralVisionAngleDegrees = 90.F;
        SightConfig->SetMaxAge(10.F); // seconds - perceived stimulus forgotten after this time
        SightConfig->AutoSuccessRangeFromLastSeenLocation = 100.F;

        SightConfig->DetectionByAffiliation.bDetectEnemies = true;
        SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
        SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

        PerceptionComponent->ConfigureSense(*SightConfig);
        PerceptionComponent->SetDominantSense(*SightConfig->GetSenseImplementation());
    }

    HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
    if (HearingConfig)
    {
        HearingConfig->HearingRange = 3000.0f;
        HearingConfig->SetMaxAge(10.F); // seconds - perceived stimulus forgotten after this time

        HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
        HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
        HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;

        PerceptionComponent->ConfigureSense(*HearingConfig);
    }

    AISense_Prediction = CreateDefaultSubobject<UAISense_Prediction>(TEXT("AISensePrediction"));

    PredictionConfig = CreateDefaultSubobject<UAISenseConfig_Prediction>(TEXT("Prediction Config"));
    if (PredictionConfig)
    {
        PredictionConfig->SetMaxAge(10.0f);

        PerceptionComponent->ConfigureSense(*PredictionConfig);
        PredictionTime = 1.0f;
    }

    PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIController_Monster::OnTargetDetected);
}

void AAIController_Monster::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
    if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
    {
        if (Actor->ActorHasTag(FName("Player")))
        {
            if (Stimulus.WasSuccessfullySensed())
            {
                Blackboard->SetValueAsObject(BBKEY_TARGET, Actor);
                UE_LOG(LogTemp, Log, TEXT("Sight"));
            }
            else
            {
                AISense_Prediction->RequestPawnPredictionEvent(GetPawn(), Cast<AActor>(Blackboard->GetValueAsObject(BBKEY_TARGET)), 1.0f);
                Blackboard->SetValueAsObject(BBKEY_TARGET, nullptr);
                Blackboard->SetValueAsVector(BBKEY_STIMULUSPOS, Stimulus.StimulusLocation);
                UE_LOG(LogTemp, Log, TEXT("SightEnd"));
            }
        }
    }
    else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
    {
        if (Stimulus.WasSuccessfullySensed())
        {
            Blackboard->SetValueAsVector(BBKEY_STIMULUSPOS, Stimulus.StimulusLocation);
            UE_LOG(LogTemp, Log, TEXT("Heard"));
        }
    }
    else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Prediction>())
    {
        if (Stimulus.WasSuccessfullySensed())
        {
            Blackboard->SetValueAsVector(BBKEY_STIMULUSPOS, Stimulus.StimulusLocation);
            UE_LOG(LogTemp, Log, TEXT("Predict"));
        }
    }
}

void AAIController_Monster::SetForget()
{
    if (PerceptionComponent)
    {
        AActor* RememberTarget = nullptr;
        // ������ ��� Ÿ�� ������ �ݺ���
        for (auto It = PerceptionComponent->GetPerceptualDataConstIterator(); It; ++It)
        {
            const FActorPerceptionInfo& PerceptionInfo = It->Value;
            // Ÿ���� "Player" �±׸� ������ �ִ��� Ȯ��
            if (PerceptionInfo.Target.Get()->ActorHasTag("Player"))
            {
                for (const FAIStimulus& Stimulus : PerceptionInfo.LastSensedStimuli)
                {
                    // �ش� Ÿ���� ���� �ڱ�(Stimuli)�� Ȯ��
                    if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
                    {
                        // Ÿ���� RememberTarget ������ ����
                        RememberTarget = PerceptionInfo.Target.Get();
                        break;
                    }
                }
            }
        }
        // Blackboard�� Ÿ�� ������ ���� (Ÿ���� ���ٸ� nullptr�� �����)
        Blackboard->SetValueAsObject(BBKEY_REMEMBERTARGET, RememberTarget);
    }
}