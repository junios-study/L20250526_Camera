// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "Perception/AIPerceptionTypes.h"
#include "Perception/AIPerceptionComponent.h"

#include "ZombieAIController.generated.h"

class UAIPerceptionComponent;

/**
 * 
 */
UCLASS()
class L20250526_CAMERA_API AZombieAIController : public AAIController
{
	GENERATED_BODY()

public:
	AZombieAIController();

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnyWhere, Category = AI, BlueprintReadWrite)
	TObjectPtr<UAIPerceptionComponent> Perception;

	//UFUNCTION()
	//void ProcessPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	UFUNCTION()
	void ProcessPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void ProcessPerceptionForgetUpdated(AActor* Actor);

	UFUNCTION()
	void ProcessPerceptionInfoUpdated(const FActorPerceptionUpdateInfo& UpdateInfo);
};
