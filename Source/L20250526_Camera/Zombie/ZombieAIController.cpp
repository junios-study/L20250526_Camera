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
	//	//�÷��̸� ã�´�.
	//	//�÷��̾ �׾����� Ȯ���Ѵ�.
	//	//���� �׾����� Ȯ���Ѵ�.
	//	if (Pawn->CurrentState == EZombieState::Patrol)
	//	{
	//		//������ ��ġ�� ���Ѵ�.
	//		//������ ��ġ�� �̵��Ѵ�.
	//	}
	//	else if(Pawn->CurrentState == EZombieState::Battle)
	//	{
	//		//�÷��̾ ���� ������ �ִ��� Ȯ���Ѵ�.
	//		//�����Ѵ�.
	//	}
	//	else if (Pawn->CurrentState == EZombieState::Chase)
	//	{
	//		//�÷��̾ �i�ư���.
	//		//���� ������ Ȯ���Ѵ�.
	//	}
	//	if (Pawn->CurrentState == EZombieState::Dead)
	//	{
	//		//3�� ��ٸ���
	//		//1�������.
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

