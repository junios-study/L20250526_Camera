// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "GameframeWork/CharacterMovementComponent.h"

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
	}
}