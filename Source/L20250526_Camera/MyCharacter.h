// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "InputActionValue.h"

#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;

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


	UPROPERTY(BlueprintReadOnly, Category = "Components", VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(BlueprintReadOnly, Category = "Components", VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	
	void OnMove(const FInputActionValue& Value);

	void OnLook(const FInputActionValue& Value);

	void OnZoom(const FInputActionValue& Value);

	void OnJump(const FInputActionValue& Value);

	



};
