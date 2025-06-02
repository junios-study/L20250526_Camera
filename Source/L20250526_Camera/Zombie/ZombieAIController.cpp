// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAIController.h"
#include "Zombie.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"

AZombieAIController::AZombieAIController()
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));

	SetPerceptionComponent(*Perception);

	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight_Config"));

	SightConfig->SightRadius = 300.0f;
	SightConfig->LoseSightRadius = 350.0f;
	SightConfig->PeripheralVisionAngleDegrees = 80.0f;
	SightConfig->SetMaxAge(1.0f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 900.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());

	//PrimaryActorTick.bCanEverTick = true;
}

void AZombieAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//AZombie* Pawn = Cast<AZombie>(GetPawn());
	//if (Pawn)
	//{
	//	//Task
	//	//플레이를 찾는다.
	//	//플레이어가 죽었는지 확인한다.
	//	//내가 죽었는지 확인한다.
	//	if (Pawn->CurrentState == EZombieState::Patrol)
	//	{
	//		//랜덤한 위치를 정한다.
	//		//정해진 위치로 이동한다.
	//	}
	//	else if(Pawn->CurrentState == EZombieState::Battle)
	//	{
	//		//플레이어가 공격 범위에 있는지 확인한다.
	//		//공격한다.
	//	}
	//	else if (Pawn->CurrentState == EZombieState::Chase)
	//	{
	//		//플레이어를 쫒아간다.
	//		//범위 밖인지 확인한다.
	//	}
	//	if (Pawn->CurrentState == EZombieState::Dead)
	//	{
	//		//3초 기다린다
	//		//1사라진다.
	//	}
	//}
}

void AZombieAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PerceptionComponent;

	AZombie* Zombie = Cast<AZombie>(InPawn);
	if (Zombie)
	{
		RunBehaviorTree(Zombie->ZombieBehaviorTree);


	}
}

void AZombieAIController::BeginPlay()
{
	Super::BeginPlay();

	BrainComponent->GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

	//Perception->OnPerceptionUpdated.AddDynamic(this, &AZombieAIController::ProcessPerceptionUpdated);

	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this,
		&AZombieAIController::ProcessPerceptionUpdated);

	GetPerceptionComponent()->OnTargetPerceptionForgotten.AddDynamic(this, &AZombieAIController::ProcessPerceptionForgetUpdated);

	GetPerceptionComponent()->OnTargetPerceptionInfoUpdated.AddDynamic(this, &AZombieAIController::ProcessPerceptionInfoUpdated);
}

//void AZombieAIController::ProcessPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
//{
//	UE_LOG(LogTemp, Warning, TEXT("ProcessPerceptionUpdated UpdatedActors"));
//}

void AZombieAIController::ProcessPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogTemp, Warning, TEXT("ProcessPerceptionUpdated Actor"));

	AZombie* Zombie = Cast<AZombie>(GetPawn());
	if (Zombie)
	{
		Zombie->CurrentState = EZombieState::Chase;
		BrainComponent->GetBlackboardComponent()->SetValueAsEnum(TEXT("CurrentState"), (uint8)(EZombieState::Chase));
	}
}

void AZombieAIController::ProcessPerceptionForgetUpdated(AActor* Actor)
{
	UE_LOG(LogTemp, Warning, TEXT("ProcessPerceptionForgetUpdated Actor"));
	AZombie* Zombie = Cast<AZombie>(GetPawn());
	if (Zombie)
	{
		Zombie->CurrentState = EZombieState::Patrol;
		BrainComponent->GetBlackboardComponent()->SetValueAsEnum(TEXT("CurrentState"), (uint8)(EZombieState::Patrol));
	}
}

void AZombieAIController::ProcessPerceptionInfoUpdated(const FActorPerceptionUpdateInfo& UpdateInfo)
{
	UE_LOG(LogTemp, Warning, TEXT("ProcessPerceptionInfoUpdated Actor"));
}

