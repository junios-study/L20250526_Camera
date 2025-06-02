// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckPlayer.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../MyCharacter.h"
#include "Zombie.h"
#include "AIController.h"

void UBTService_CheckPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AMyCharacter* Character = Cast<AMyCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	//AMyCharacter* Character = Cast<AMyCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Player"))));
	if (Character)
	{
		float Distance = FVector::Distance(Character->GetActorLocation(), OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation());

		AZombie* Zombie = Cast<AZombie>(OwnerComp.GetAIOwner()->GetPawn());
		if (Zombie)
		{
			UE_LOG(LogTemp, Warning, TEXT("Distance %f"), Distance);

			if (Distance > 350.0f && Zombie->CurrentState == EZombieState::Chase)
			{
				Zombie->CurrentState = EZombieState::Patrol;
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)EZombieState::Patrol);
			}
		}
	}
}
