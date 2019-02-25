// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utils/Singleton.h"
#include "Sound/AmbientSound.h"
#include "Sound/BGMActor.h"

/**
 * 
 */
class SOUNDMANAGERTESTPROJ_API SoundManager : public TSingleton<SoundManager>
{
	TWeakObjectPtr<ABGMActor> m_pBGMActor;
	TWeakObjectPtr<USoundConcurrency> m_pConcurrency;
	TMap<FString, USoundBase*> m_SoundMap;

	TWeakObjectPtr<UWorld> m_pWorld;
	UWorld* GetWorld() const { return m_pWorld.Get(); }

public:
	SoundManager();
	~SoundManager();

	void Initialize(UWorld* InWorld);

	bool Load(const FString& InPath);
	void PlayEffect(const FString& InPath);
	void PlayBGM(const FString& InPath, bool InIsFadeIn = false, float InFadeInDuration = 1.0f, float InFadeVolumeLevel = 1.0f);
	void StopBGM(bool InIsFadeOut = false, float InFadeOutDuration = 1.0f, float InFadeVolumeLevel = 1.0f);

};
