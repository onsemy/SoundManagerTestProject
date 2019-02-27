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
	TMap<int, TWeakObjectPtr<ABGMActor>> m_BGMActorMap;
	TWeakObjectPtr<USoundConcurrency> m_pBGMConcurrency;
	TWeakObjectPtr<USoundConcurrency> m_pEffectConcurrency;
	TMap<FString, USoundWave*> m_SoundMap;

	TWeakObjectPtr<UWorld> m_pWorld;
	UWorld* GetWorld() const { return m_pWorld.Get(); }
	int m_nCurrentBGMIndex;

public:
	SoundManager();
	~SoundManager();

	void Initialize(UWorld* InWorld);

	bool Load(const FString& InPath);
	void UnloadAll();
	void PlayEffect(const FString& InPath);
	void PlayBGM(int InBGMType, const FString& InPath, bool InIsFadeIn = false, float InFadeInDuration = 1.0f);
	void StopBGM(int InBGMType, bool InIsFadeOut = false, float InFadeOutDuration = 1.0f);

	void SetBGMConcurrency(USoundConcurrency* InConcurrency) { m_pBGMConcurrency = InConcurrency; }
	void SetEffectConcurrency(USoundConcurrency* InConcurrency) { m_pEffectConcurrency = InConcurrency; }

};
