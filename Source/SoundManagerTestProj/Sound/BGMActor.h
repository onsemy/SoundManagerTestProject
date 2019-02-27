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

	TMap<int, TArray<TWeakObjectPtr<UAudioComponent>>> m_AudioComponentMap;
	TWeakObjectPtr<USoundConcurrency> m_pSoundConcurrency;

	bool IsVolumeTweening;
	
public:	
	ABGMActor();

	void SetConcurrency(USoundConcurrency* InConcurrency);

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;

public:	
	void PlayBGM(int InBGMType, USoundWave* InSound, bool InIsCrossFade = false, float InCrossFadeDuration = 1.0f);
	void StopBGM(int InBGMType, bool InIsFadeOut = false, float InFadeOutDuration = 1.0f);
	bool IsPlaying(int InBGMType);

private:
	void PlayBGM_Internal(int InBGMType, USoundWave* InSound, bool InIsCrossFade = false, float InCrossFadeDuration = 1.0f);
	void StopBGM_Internal(int InBGMType, bool InIsFadeOut = false, float InFadeOutDuration = 1.0f);

};
