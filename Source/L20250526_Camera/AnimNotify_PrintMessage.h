// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_PrintMessage.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Print Message"))
class L20250526_CAMERA_API UAnimNotify_PrintMessage : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, Category="Data", BlueprintReadWrite)
	FString PrintMessage;
};
