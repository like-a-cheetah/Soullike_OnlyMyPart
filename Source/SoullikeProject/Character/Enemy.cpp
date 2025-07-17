// Fill out your copyright notice in the Description page of Project Settings.

//기본 헤더
#include "Character/Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

//불러온 기본 헤더
#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

//불러온 만든 헤더
//#include "CharacterStat/CharacterStatComponent.h"
//#include "CharacterStat/HpBarWidget.h"
//#include "CharacterStat/MyWidgetComponent.h"
#include "AI/AI_Grux/AIController_Monster.h"
//#include "PracPlayer/GreyStone.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	//GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_ABCAPSULE);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	SetupRef();

	//Stat Component
	//Stat = CreateDefaultSubobject<UCharacterStatComponent>(TEXT("Stat"));

	//Widget Component
	//HPBar = CreateDefaultSubobject<UMyWidgetComponent>(TEXT("Widget"));
	//HPBar->SetupAttachment(GetMesh());
	//HPBar->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	/*static ConstructorHelpers::FClassFinder<UUserWidget> HPBarWidgetRef(TEXT("/Game/UI/HPBar.HPBar_C"));
	if (HPBarWidgetRef.Class)
	{
		HPBar->SetWidgetClass(HPBarWidgetRef.Class);
		HPBar->SetWidgetSpace(EWidgetSpace::Screen);
		HPBar->SetDrawSize(FVector2D(150.0f, 15.0f));
		HPBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}*/

	//AIControllerClass = AAIController_Monster::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	LWeaponCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LWeapon"));
	//LWeaponCollision->SetCollisionProfileName(CPROFILE_ABTRIGGER);
	LWeaponCollision->InitCapsuleSize(10.f, 80.0f);

	FName Socket1Name = FName(TEXT("weapon_l_Socket"));
	const USkeletalMeshSocket* LWeaponSocket = GetMesh()->GetSocketByName(Socket1Name);
	if (LWeaponSocket)
	{
		LWeaponCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, Socket1Name);
		FVector CurrentLocation = LWeaponCollision->GetComponentLocation();
		CurrentLocation += FVector(0, LWeaponCollision->GetScaledCapsuleHalfHeight(), 0);
		LWeaponCollision->SetWorldLocation(CurrentLocation);
		LWeaponCollision->bHiddenInGame = false;
	}

	RWeaponCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RWeapon"));
	//RWeaponCollision->SetCollisionProfileName(CPROFILE_ABTRIGGER);
	RWeaponCollision->InitCapsuleSize(10.f, 80.0f);

	FName Socket2Name = FName(TEXT("weapon_r_Socket"));
	const USkeletalMeshSocket* RWeaponSocket = GetMesh()->GetSocketByName(Socket2Name);
	if (RWeaponSocket)
	{
		RWeaponCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, Socket2Name);
		FVector CurrentLocation = RWeaponCollision->GetComponentLocation();
		CurrentLocation += FVector(0, -RWeaponCollision->GetScaledCapsuleHalfHeight(), 0);
		RWeaponCollision->SetWorldLocation(CurrentLocation);
		RWeaponCollision->bHiddenInGame = false;
	}
}

void AEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//Stat->OnHPZero.AddUObject(this, &AEnemy::SetDead);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	LWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::BeginOverlapLWeapon);
	RWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::BeginOverlapRWeapon);
	LWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GetHeadLookRotation();
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::SetupRef()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGrux/Characters/Heroes/Grux/Meshes/Grux.Grux'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/Animation/AnimBlueprint_Grux.AnimBlueprint_Grux_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animation/Etc/MT_Death_B.MT_Death_B'"));
	if (DeadMontageRef.Object)
	{
		DeadMontage = DeadMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> HittedMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animation/Etc/MT_Hitted.MT_Hitted'"));
	if (HittedMontageRef.Object)
	{
		HittedMontage = HittedMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> StempedeMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animation/Stampede/MT_Stampede.MT_Stampede'"));
	if (StempedeMontageRef.Object)
	{
		StampedeMontage = StempedeMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Stampede_KnockupMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animation/Stampede_Knockup/MT_Stampede_Knockup.MT_Stampede_Knockup'"));
	if (Stampede_KnockupMontageRef.Object)
	{
		Stampede_KnockupMontage = Stampede_KnockupMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Ultimate_RoarMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animation/Etc/MT_Ultimate_Roar.MT_Ultimate_Roar'"));
	{
		Ultimate_RoarMontage = Ultimate_RoarMontageRef.Object;
	}
}

void AEnemy::ComboActionBegin(int MontageNum)
{
	// Movement Setting
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	// Animation Setting
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (AttackMontages.IsEmpty())
	{
		UE_LOG(LogTemp, Log, TEXT("공격 설정 안돼있음"));
		return;
	}

	AnimInstance->Montage_Play(AttackMontages[MontageNum], 1.f);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &AEnemy::ComboActionEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, AttackMontages[MontageNum]);
}

void AEnemy::ComboActionEnd(UAnimMontage* TargetMontage, bool IsProperlyEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	AttackTaskEnd();
}

void AEnemy::AttackTaskEnd()
{
	OnAttackFinished.ExecuteIfBound();	//콤보가 끝났다는 것을 알리는 델리게이트 호출
}

void AEnemy::AttackHitCheck()
{
	const float AttackRange = 180.0f;
	const float AttackRadius = 10.0f;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);
	TArray<FHitResult> OutHitResults;

	FVector LStart = GetMesh()->GetSocketLocation(FName(TEXT("weapon_l_Start")));
	FVector LEnd = GetMesh()->GetSocketLocation(FName(TEXT("weapon_l_End")));

	//bool HitDetected = GetWorld()->SweepMultiByChannel(OutHitResults, LStart, LEnd, FQuat::Identity, CCHANNEL_ABACTION, FCollisionShape::MakeCapsule(AttackRadius, AttackRange), Params);
	//if (HitDetected)
	//{
	//	FDamageEvent DamageEvent;
	//	//OutHitResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
	//	HitDetected = false;
	//}

	FVector RStart = GetMesh()->GetSocketLocation(FName(TEXT("weapon_r_Start")));
	FVector REnd = GetMesh()->GetSocketLocation(FName(TEXT("weapon_r_End")));

	//HitDetected = GetWorld()->SweepMultiByChannel(OutHitResults, RStart, REnd, FQuat::Identity, CCHANNEL_ABACTION, FCollisionShape::MakeCapsule(AttackRadius, AttackRange), Params);
	//if (HitDetected)
	//{
	//	FDamageEvent DamageEvent;
	//	//OutHitResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
	//}

	float CapsuleHeight = AttackRange * 0.5f;
	//FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

	FVector CapsuleOrigin;
	FVector StartToEnd;
}

void AEnemy::HitStart()
{
	//LWeaponCollision->SetActive(true);
	LWeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	RWeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	bIsPlayerHitted = false;
	bHitCheck = true;
}

void AEnemy::HitEnd()
{
	//LWeaponCollision->SetActive(false);
	LWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bIsPlayerHitted = false;
	bHitCheck = false;
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{																			  //가해자						//무기 or 폰의 액터 정보
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	UE_LOG(LogTemp, Log, TEXT("플레이어에게 데미지받음!"));
	//Stat->ApplyDamage(DamageAmount);

	UE_LOG(LogTemp, Log, TEXT("히트 애니메이션"));

	//if (Stat->GetCurrentHP())
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		//if (Stat->GetCurrentHP() / Stat->GetMaxHP() > 0.5f)
		//{
		//	AnimInstance->Montage_Play(HittedMontage, 1.0f, EMontagePlayReturnType::MontageLength, 0.0f, false);
		//}
		//else
		//{
		//	AAIController_Monster* AIController = Cast<AAIController_Monster>(GetController());
		//	AnimInstance->Montage_Play(HittedMontage);
		//}
	}

	//최종으로 액터가 받은 데미지 반환
	return DamageAmount;
}

void AEnemy::BeginOverlapLWeapon(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (Cast<AGreyStone>(OtherActor))
	//{
		//FDamageEvent DamageEvent;
		//OtherActor->TakeDamage(5, DamageEvent, GetController(), this);
	//}
}

void AEnemy::EndOverlapLWeapon(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AEnemy::BeginOverlapRWeapon(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (Cast<AGreyStone>(OtherActor))
	//{
	//	FDamageEvent DamageEvent;
	//	OtherActor->TakeDamage(5.0f, DamageEvent, GetController(), this);

	//	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	//	if (AnimInstance->GetCurrentActiveMontage()->GetName().Equals(TEXT("MT_Stampede_Knockup")))
	//	{
	//		FVector Direction = OtherActor->GetActorLocation() -GetActorLocation();
	//		Direction = { Direction.X, Direction.Y, 0.0f };
	//		Direction *= 10.0f;

	//if(Cast<ACharacter>(OtherActor))
		//Cast<ACharacter>(OtherActor)->LaunchCharacter(FVector(Direction.X, Direction.Y, 600.0f), true, true);

			//GetActorLocation();
	//		bIsPlayerHitted = true;
	//		UE_LOG(LogTemp, Log, TEXT("에어본"));
	//	}

	//	UE_LOG(LogTemp, Log, TEXT("40 데미지줌!"));
	//}
}

void AEnemy::EndOverlapRWeapon(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AEnemy::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadAnimation();
	SetActorEnableCollision(false);

	AAIController_Monster* AIController = Cast<AAIController_Monster>(GetController());
	if (AIController)
	{
		AIController->StopAI();
		UE_LOG(LogTemp, Log, TEXT("Stop"));
	}

//HPBar->SetHiddenInGame(true);

	//ACharacter* c = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	//if (c)
	//{
//		AGreyStone* p = Cast<AGreyStone>(c);
		//if (p)
		//{
		//	p->GetStatComponent()->SetMoney(p->GetStatComponent()->GetCurMoney() + 50);
		//}
	//}
		
	DoDisappear();
}

void AEnemy::PlayDeadAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	//AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(DeadMontage, 1.f);

	FTimerHandle StopMontage;

	UWorld* TempWorld = GetWorld();
	if (TempWorld)
	{
		GetWorld()->GetTimerManager().SetTimer(StopMontage, FTimerDelegate::CreateLambda(
			[&]()
		{
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance)
				AnimInstance->Montage_Pause(DeadMontage);
			else
				UE_LOG(LogTemp, Log, TEXT("AnimInstance"));


		}
		), 1.3f, false);
	}
}

void AEnemy::DoDisappear()
{
	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);
}

void AEnemy::SetupCharacterWidget(UMyUserWidget* InUserWidget)
{
//	UHPBarWidget* HPBarWidget = Cast<UHPBarWidget>(InUserWidget);
	//if (HPBarWidget)
	//{
		//HPBarWidget->SetMaxHP(Stat->GetMaxHP());
		//HPBarWidget->UpdateHPBar(Stat->GetCurrentHP());
		//Stat->OnHPChanged.AddUObject(HPBarWidget, &UHPBarWidget::UpdateHPBar);	//델리게이트에 UpdateHPBar 함수 등록
	//}
}

float AEnemy::GetAIPatrolRadius()
{
	return 800.0f;
}

float AEnemy::GetAIDetectRange()
{
	return 1000.0f;
}

float AEnemy::GetAIAttackRange()
{
	return 250.0f;//Stat->GetAttackRadius() * 2.0f;
}

float AEnemy::GetAITurnSpeed()
{
	return 0.0f;
}

void AEnemy::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void AEnemy::AttackByAI(int MontageNum)
{
	ComboActionBegin(MontageNum);

	SetVelocity(600.0f);	//임시
}

void AEnemy::OnAlertMovement()
{
	bIsAlert = true;
	SetbOrientRotationToMovement(false);
}

void AEnemy::OffAlertMovement()
{
	bIsAlert = false;
	SetbOrientRotationToMovement(true);
}

void AEnemy::SetVelocity(float Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void AEnemy::SetbOrientRotationToMovement(bool val)
{
	GetCharacterMovement()->bOrientRotationToMovement = val;	//임시
}

void AEnemy::TimerSetMovementModeWalking()
{

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AEnemy::Stampede_Knockup(FVector TargetPos)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(Stampede_KnockupMontage, 1.f);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &AEnemy::ComboActionEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, Stampede_KnockupMontage);

	FVector Direction = TargetPos - GetActorLocation();
	Direction = Direction.GetSafeNormal(1.0f);
	Direction *= 800.0f;
	Direction.Z = 400.0f;

	GetCharacterMovement()->AddImpulse(Direction, true);
}

void AEnemy::Stampede()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(StampedeMontage, 1.f);

	SetVelocity(1000.0f);
}

//void AEnemy::CallTheTeam()
//{
//	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
//
//	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
//	AnimInstance->Montage_Play(Ultimate_RoarMontage, 1.f);
//
//	FOnMontageEnded EndDelegate;
//	EndDelegate.BindUObject(this, &AEnemy::ComboActionEnd);
//	AnimInstance->Montage_SetEndDelegate(EndDelegate, Ultimate_RoarMontage);
//}

void AEnemy::SetLookRotation(float Rotation)
{
	LookRotation = Rotation;
}

void AEnemy::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	FTransform HeadTransform = GetMesh()->GetSocketTransform(FName("headSocket"));
	OutLocation = HeadTransform.GetLocation();
	OutRotation = HeadTransform.Rotator();
}
