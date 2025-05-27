// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_PrintMessage.h"


void UAnimNotify_PrintMessage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *PrintMessage);
}