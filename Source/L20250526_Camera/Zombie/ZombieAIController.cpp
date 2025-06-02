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
