// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "Zombie.h"

#include "BTTaskNode_CheckDistance.generated.h"

UENUM(BlueprintType)
enum class ECondition : uint8
{
	LessThen			= 0		UMETA(DisplayName = "<"),
	GreaterThen			= 1		UMETA(DisplayName = ">")
};

/**
 * 
 */
UCLASS()
class L20250526_CAMERA_API UBTTaskNode_CheckDistance : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	ECondition TargetCondition;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	EZombieState TargetState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	float TargetDistance;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
