// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Zombie.generated.h"

class UBehaviorTree;

UENUM(BlueprintType)
enum class EZombieState : uint8
{
	Patrol	= 0 UMETA(DisplayName = "Patrol"),
	Battle	= 1 UMETA(DisplayName = "Battle"),
	Chase	= 2 UMETA(DisplayName = "Chase"),
	Dead	= 3 UMETA(DisplayName = "Dead")
};


UCLASS()
class L20250526_CAMERA_API AZombie : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, Category="State", EditAnywhere)
	EZombieState CurrentState;

	UPROPERTY(BlueprintReadWrite, Category = "AI", EditAnywhere)
	TObjectPtr<UBehaviorTree> ZombieBehaviorTree;

};
