// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/AmbientSound.h"
#include "BGMActor.generated.h"

UCLASS()
class SOUNDMANAGERTESTPROJ_API ABGMActor : public AAmbientSound
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABGMActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void PlayBGM(USoundWave* InSound, bool IsFadeIn = false, float InFadeInDuration = 1.0f, float InFadeVolumeLevel = 1.0f);
	void StopBGM(bool InIsFadeOut = false, float InFadeOutDuration = 1.0f, float InFadeVolumeLevel = 1.0f);

};
