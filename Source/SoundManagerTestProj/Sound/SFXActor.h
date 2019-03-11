// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SFXActor.generated.h"

UCLASS()
class SOUNDMANAGERTESTPROJ_API ASFXActor : public AActor
{
	GENERATED_BODY()

	TWeakObjectPtr<USoundWave> m_pSoundWave;
	TWeakObjectPtr<UAudioComponent> m_pAudioComponent;
	TWeakObjectPtr<USoundConcurrency> m_pSoundConcurrency;

public:
	// Sets default values for this actor's properties
	ASFXActor();

	void PlayEffect(USoundWave* InSound, float InVolume = 1.0f);
	void StopEffect();

	void SetConcurrency(USoundConcurrency* InSoundConcurrency) { m_pSoundConcurrency = InSoundConcurrency; }

	UFUNCTION()
	void OnAudioFinished();

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnAudioFinishedDelegate, USoundWave*);
	FOnAudioFinishedDelegate AudioFinishedDelegate;

};
