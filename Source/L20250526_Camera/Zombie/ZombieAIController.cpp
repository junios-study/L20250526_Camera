// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAIController.h"
#include "Zombie.h"

AZombieAIController::AZombieAIController()
{
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
