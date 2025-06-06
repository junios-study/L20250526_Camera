// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

//#include "AnimInstance.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		FRotator(0, -90, 0));

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));

	PerceptionStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("PerceptionSimuli"));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (PerceptionStimuliSource)
	{
		UE_LOG(LogTemp, Warning, TEXT("PerceptionStimuliSource RegisterForSense"));
		PerceptionStimuliSource->RegisterForSense(UAISense_Sight::StaticClass());
		PerceptionStimuliSource->RegisterWithPerceptionSystem();
	}


}

// Ca lled every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* UEIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UEIC)
	{
		UEIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMyCharacter::OnMove);
		UEIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMyCharacter::OnLook);
		UEIC->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AMyCharacter::OnJump);
		UEIC->BindAction(IA_Zoom, ETriggerEvent::Triggered, this, &AMyCharacter::OnZoom);

		UEIC->BindAction(IA_Crouch, ETriggerEvent::Triggered, this, &AMyCharacter::OnCrouch);

		UEIC->BindAction(IA_Reload, ETriggerEvent::Triggered, this, &AMyCharacter::OnReload);

		UEIC->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AMyCharacter::OnFire);

		UEIC->BindAction(IA_Fire, ETriggerEvent::Completed, this, &AMyCharacter::OnEndFire);

		UEIC->BindAction(IA_LeftLean, ETriggerEvent::Triggered, this, &AMyCharacter::OnLeftLean);

		UEIC->BindAction(IA_LeftLean, ETriggerEvent::Completed, this, &AMyCharacter::OnEndLeftLean);

		UEIC->BindAction(IA_RightLean, ETriggerEvent::Triggered, this, &AMyCharacter::OnRightLean);

		UEIC->BindAction(IA_RightLean, ETriggerEvent::Completed, this, &AMyCharacter::OnEndRightLean);

	}

}

void AMyCharacter::OnMove(const FInputActionValue& Value)
{
	FVector2D DirectionVector = Value.Get<FVector2D>();

	FRotator CameraRotation = GetControlRotation();

	FRotator FloorProjectionRotation = FRotator(0, CameraRotation.Yaw, CameraRotation.Roll);
	FVector CameraForward = UKismetMathLibrary::GetForwardVector(FloorProjectionRotation);
	FVector CameraRight = UKismetMathLibrary::GetRightVector(FloorProjectionRotation);

	AddMovementInput(CameraForward, DirectionVector.Y);
	AddMovementInput(CameraRight, DirectionVector.X);
}
void AMyCharacter::OnLook(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();




	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);

}

void AMyCharacter::OnZoom(const FInputActionValue& Value)
{
	//SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, SpringArm->TargetArmLength + Value.Get<float>() * -200.0f, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 10.0f);
	SpringArm->TargetArmLength += Value.Get<float>() * -10.0f;
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength,
		100.0f,
		600.0f);
}

void AMyCharacter::OnJump(const FInputActionValue& Value)
{
	Jump();
}

void AMyCharacter::OnCrouch(const FInputActionValue& Value)
{
	if (CanCrouch())
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void AMyCharacter::OnReload(const FInputActionValue& Value)
{
	if (AM_Reload)
	{
		if (!GetMesh()->GetAnimInstance()->Montage_IsPlaying(AM_Reload))
		{
			PlayAnimMontage(AM_Reload, 1.0f, TEXT("Rifle"));
		}
	}

	//if (AM_Hit)
	//{
	//	int HitNo = FMath::RandRange(1, 4);
	//	FString Temp = FString::Printf(TEXT("Hit_%d"), HitNo);
	//	PlayAnimMontage(AM_Hit, 1.0f, *Temp);
	//}
}

void AMyCharacter::OnFire(const FInputActionValue& Value)
{
	bIsFire = true;
}

void AMyCharacter::OnLeftLean(const FInputActionValue& Value)
{
	bIsLeftLean = true;
}

void AMyCharacter::OnRightLean(const FInputActionValue& Value)
{
	bIsRightLean = true;
}

void AMyCharacter::OnEndFire(const FInputActionValue& Value)
{
	bIsFire = false;
}

void AMyCharacter::OnEndLeftLean(const FInputActionValue& Value)
{
	bIsLeftLean = false;
}

void AMyCharacter::OnEndRightLean(const FInputActionValue& Value)
{
	bIsRightLean = false;
}




