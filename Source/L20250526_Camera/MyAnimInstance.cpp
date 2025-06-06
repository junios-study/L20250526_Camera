﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "GameframeWork/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"


void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	//Pawn 정보를 가져온다.
	//Pawn의 속성을 멤버 변수로 만든다.
	//Pawn의 정보를 가져옴
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMyCharacter* Pawn = Cast<AMyCharacter>(TryGetPawnOwner());
	if (IsValid(Pawn))
	{
		Speed = Pawn->GetCharacterMovement()->Velocity.Size2D();
		bIsCrouched = !Pawn->CanCrouch();
		Direction = UKismetAnimationLibrary::CalculateDirection(Pawn->GetCharacterMovement()->Velocity,
			Pawn->GetActorRotation());
		bIsFire = Pawn->bIsFire;
		bIsLeftLean = Pawn->bIsLeftLean;
		bIsRightLean = Pawn->bIsRightLean;

		if (bIsLeftLean)
		{
			TargetSpineAngle = -30.0f;
		}

		if (bIsRightLean)
		{
			TargetSpineAngle = 30.0f;
		}

		if (!bIsRightLean && !bIsLeftLean)
		{
			TargetSpineAngle = 0.0f;
		}

		CurrentSpineAngle = FMath::FInterpTo(CurrentSpineAngle, TargetSpineAngle, DeltaSeconds, 8.0f);

		AimYaw = Pawn->GetBaseAimRotation().Yaw;
		AimPitch = Pawn->GetBaseAimRotation().Pitch;
	}
}

void UMyAnimInstance::AnimNotify_HelloWorldCpp(UAnimNotify* Notify)
{
	UE_LOG(LogTemp, Warning, TEXT("HelloWorldCPP"));
}
