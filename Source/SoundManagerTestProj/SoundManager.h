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
	TMap<FString, USoundBase*> m_SoundMap;

	TWeakObjectPtr<UWorld> m_pWorld;
	UWorld* GetWorld() const { return m_pWorld.Get(); }

public:
	SoundManager();
	~SoundManager();

	void Initialize(UWorld* InWorld) { m_pWorld = InWorld; }

	void Load(const FString& InPath);
	void PlayEffect();
	void PlayBGM(const FString& InPath);

};
