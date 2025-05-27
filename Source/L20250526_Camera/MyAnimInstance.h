// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class L20250526_CAMERA_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, Category = "State", VisibleAnywhere)
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category = "State", VisibleAnywhere)
	uint8 bIsCrouched : 1;

	UPROPERTY(BlueprintReadOnly, Category = "State", VisibleAnywhere)
	float Direction;

	//skeleton animnotify -> skeleton ����
	UFUNCTION()
	void AnimNotify_HelloWorldCpp(UAnimNotify* Notify);
};
