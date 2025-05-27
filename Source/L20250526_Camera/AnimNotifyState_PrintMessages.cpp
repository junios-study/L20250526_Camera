// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_PrintMessages.h"

void UAnimNotifyState_PrintMessages::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	UE_LOG(LogTemp, Warning, TEXT("NotifyBegin"));
	Count = 0;
}


void UAnimNotifyState_PrintMessages::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	UE_LOG(LogTemp, Warning, TEXT("Tick %d"), Count++);
}



void UAnimNotifyState_PrintMessages::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	UE_LOG(LogTemp, Warning, TEXT("NotifyEnd"));
}