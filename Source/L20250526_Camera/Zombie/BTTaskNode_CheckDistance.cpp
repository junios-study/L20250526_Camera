// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_CheckDistance.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Zombie.h"

EBTNodeResult::Type UBTTaskNode_CheckDistance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	FVector OwnerLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();

	AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Player")));
	if (Player)
	{
		float Distance = FVector::Distance(OwnerLocation, Player->GetActorLocation());
		if (TargetCondition == ECondition::LessThen)
		{
			if (Distance < TargetDistance)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("CurrentState"), (uint8)(TargetState));
				AZombie* Zombie = Cast<AZombie>(OwnerComp.GetAIOwner()->GetPawn());
				Zombie->CurrentState = TargetState;
			}
		}
		else if (TargetCondition == ECondition::GreaterThen)
		{
			if (Distance > TargetDistance)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("CurrentState"), (uint8)(TargetState));
				AZombie* Zombie = Cast<AZombie>(OwnerComp.GetAIOwner()->GetPawn());
				Zombie->CurrentState = TargetState;
			}
		}

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
