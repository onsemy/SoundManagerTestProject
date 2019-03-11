// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utils/Singleton.h"
#include "Sound/BGMActor.h"
#include "Sound/SFXActor.h"

/**
 * 
 */
class SOUNDMANAGERTESTPROJ_API SoundManager : public TSingleton<SoundManager>
{
	bool m_bInit = false;

	TMap<int, TWeakObjectPtr<ABGMActor>> m_BGMActorMap;
	TWeakObjectPtr<USoundClass> m_pBGMClass;
	TWeakObjectPtr<USoundClass> m_pEffectClass;
	TWeakObjectPtr<USoundConcurrency> m_pBGMConcurrency;
	TWeakObjectPtr<USoundConcurrency> m_pEffectConcurrency;

	int m_nCurrentEffectIndex = 0;
	int m_nEffectMaxCount = 10;
	TMap<int, TWeakObjectPtr<ASFXActor>> m_EffectActorMap;

	TMap<FString, USoundWave*> m_SoundMap;
	TMap<USoundWave*, int> m_SoundReferenceMap;

	TMap<int, FString> m_LatestBGMPathMap;

	TWeakObjectPtr<UWorld> m_pWorld;
	UWorld* GetWorld() const { return m_pWorld.Get(); }
	int m_nCurrentBGMIndex;

	bool m_bIsMute = false;

	FString m_pPrevBGMPath;

public:
	SoundManager();
	~SoundManager();

	void Initialize(UWorld* InWorld, const FString& InBGMClass, const FString& InEffectClass, const FString& InBGMConcurrency, const FString& InEffectConcurrency, const int InMaxBGMCount);
	bool IsInitialize() { return m_bInit; }

private:
	ABGMActor* GetBGMActor(int InBGMType);
	ASFXActor* GetEffectActor(int InIndex);

public:
	bool Load(const FString& InPath);
	void UnloadAll();
	void PlayEffect(const FString& InPath);
	void PlayBGM(int InBGMType, const FString& InPath, bool InIsFadeIn = false, float InTargetVolume = 1.0f, float InFadeInDuration = 1.0f);
	void PlayPrevBGM(int InBGMType, bool InIsFadeIn = false, float InTargetVolume = 1.0f, float InFadeInDuration = 1.0f);
	void StopBGM(int InBGMType, bool InIsFadeOut = false, float InTargetVolume = 0.0f, float InFadeOutDuration = 1.0f);
	void StopAllBGM(bool InIsFadeOut = false, float InFadeOutDuration = 1.0f);
	void StopAllEffect();
	void SaveLatestBGMPath(int InBGMType);

	void SetBGMConcurrency(USoundConcurrency* InConcurrency) { m_pBGMConcurrency = InConcurrency; }
	void SetBGMConcurrency(const FString& InPath);
	void SetEffectConcurrency(USoundConcurrency* InConcurrency) { m_pEffectConcurrency = InConcurrency; }
	void SetEffectConcurrency(const FString& InPath);

	void SetBGMVolume(int InBGMType, float InVolume, bool InIsTweening = false, float InDuration = 0.0f);
	void SetBGMAllVolume(float InVolume);
	void SetEffectAllVolume(float InVolume);
	void SetMute(bool InIsMute);

private:
	void AddReferenceCount(USoundWave* InSound);
	void RemoveReferenceCount(USoundWave* InSound);

};
