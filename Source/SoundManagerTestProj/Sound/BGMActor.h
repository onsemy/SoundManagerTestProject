// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "BGMActor.generated.h"

UCLASS()
class SOUNDMANAGERTESTPROJ_API ABGMActor : public AActor
{
	GENERATED_BODY()

	TArray<TWeakObjectPtr<UAudioComponent>> m_AudioComponentList;
	TWeakObjectPtr<USoundConcurrency> m_pSoundConcurrency;

	float m_fTargetVolume;
	float m_fOriginVolume;
	float m_fCurrentVolume;

	float m_fTargetDuration;
	float m_fCurrentDuration;

	bool m_bIsVolumeTweening;
	
public:	
	ABGMActor();

	void SetConcurrency(USoundConcurrency* InConcurrency);

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;

public:	
	void PlayBGM(USoundWave* InSound, bool InIsCrossFade = false, float InCrossFadeDuration = 1.0f);
	void StopBGM(bool InIsFadeOut = false, float InFadeOutDuration = 1.0f);
	bool IsPlaying();

	void SetVolume(float InVolume, bool InIsTweening = false, float InDuration = 0.0f);

private:
	void PlayBGM_Internal(USoundWave* InSound, bool InIsCrossFade = false, float InCrossFadeDuration = 1.0f);
	void StopBGM_Internal(bool InIsFadeOut = false, float InFadeOutDuration = 1.0f);

};
