// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "InputActionValue.h"

#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UAIPerceptionStimuliSourceComponent;


UCLASS()
class L20250526_CAMERA_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(BlueprintReadOnly, Category ="Input", EditAnywhere)
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(BlueprintReadOnly, Category = "Input", EditAnywhere)
	TObjectPtr<UInputAction> IA_Look;

	UPROPERTY(BlueprintReadOnly, Category = "Input", EditAnywhere)
	TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(BlueprintReadOnly, Category = "Input", EditAnywhere)
	TObjectPtr<UInputAction> IA_Zoom;

	UPROPERTY(BlueprintReadOnly, Category = "Input", EditAnywhere)
	TObjectPtr<UInputAction> IA_Crouch;

	UPROPERTY(BlueprintReadOnly, Category = "Input", EditAnywhere)
	TObjectPtr<UInputAction> IA_Reload;

	UPROPERTY(BlueprintReadOnly, Category = "Input", EditAnywhere)
	TObjectPtr<UInputAction> IA_Fire;

	UPROPERTY(BlueprintReadOnly, Category = "Input", EditAnywhere)
	TObjectPtr<UInputAction> IA_LeftLean;

	UPROPERTY(BlueprintReadOnly, Category = "Input", EditAnywhere)
	TObjectPtr<UInputAction> IA_RightLean;

	UPROPERTY(BlueprintReadOnly, Category = "Input", EditAnywhere)
	TObjectPtr<UInputMappingContext> IMC_Default;


	UPROPERTY(BlueprintReadOnly, Category = "Components", VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(BlueprintReadOnly, Category = "Components", VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(BlueprintReadOnly, Category = "Components", VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(BlueprintReadOnly, Category = "Components", VisibleAnywhere)
	TObjectPtr<UAIPerceptionStimuliSourceComponent> PerceptionStimuliSource;

	
	void OnMove(const FInputActionValue& Value);

	void OnLook(const FInputActionValue& Value);

	void OnZoom(const FInputActionValue& Value);

	void OnJump(const FInputActionValue& Value);

	void OnCrouch(const FInputActionValue& Value);

	void OnReload(const FInputActionValue& Value);

	void OnFire(const FInputActionValue& Value);

	void OnLeftLean(const FInputActionValue& Value);

	void OnRightLean(const FInputActionValue& Value);

	void OnEndFire(const FInputActionValue& Value);

	void OnEndLeftLean(const FInputActionValue& Value);

	void OnEndRightLean(const FInputActionValue& Value);

	

	UPROPERTY(BlueprintReadOnly, Category = "Animations", EditAnywhere)
	TObjectPtr<UAnimMontage> AM_Reload;

	UPROPERTY(BlueprintReadOnly, Category = "Animations", EditAnywhere)
	TObjectPtr<UAnimMontage> AM_Hit;



	UPROPERTY(BlueprintReadOnly, Category = "State", EditAnywhere)
	uint8 bIsFire : 1;

	UPROPERTY(BlueprintReadOnly, Category = "State", EditAnywhere)
	uint8 bIsLeftLean : 1;

	UPROPERTY(BlueprintReadOnly, Category = "State", EditAnywhere)
	uint8 bIsRightLean : 1;

};
