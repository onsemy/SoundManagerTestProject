// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundManager.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

SoundManager::SoundManager()
{
	m_nCurrentBGMIndex = 0;
}

SoundManager::~SoundManager()
{
	m_SoundMap.Empty();
	for (TWeakObjectPtr<ABGMActor> BGMActor : m_pBGMActorList)
	{
		BGMActor->RemoveFromRoot();
	}
	m_pBGMActorList.Empty();
	m_pEffectConcurrency = nullptr;
	m_pWorld = nullptr;
}

void SoundManager::Initialize(UWorld* InWorld)
{
	m_pWorld = InWorld;

	for (int i = 0; i < 2; ++i)
	{
		ABGMActor* Actor = InWorld->SpawnActor<ABGMActor>();
		Actor->AddToRoot();
		m_pBGMActorList.Add(Actor);
	}

	m_pEffectConcurrency = LoadObject<USoundConcurrency>(nullptr, TEXT("SoundConcurrency'/Game/Sound/NewSoundConcurrency.NewSoundConcurrency'"));
}

bool SoundManager::Load(const FString& InPath)
{
	if (m_SoundMap.Contains(InPath) == false)
	{
		USoundWave* Sound = LoadObject<USoundWave>(nullptr, *InPath);
		if (Sound == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load sound - %s"), *InPath);
			return false;
		}

		m_SoundMap.Add(InPath, Sound);
	}

	return true;
}

void SoundManager::UnloadAll()
{
	m_SoundMap.Empty();
}

void SoundManager::PlayEffect(const FString& InPath)
{
	if (Load(InPath) == false)
	{
		return;
	}

	UGameplayStatics::PlaySound2D(GetWorld(), m_SoundMap[InPath], 1.0f, 1.0f, 0.0f, m_pEffectConcurrency.Get());
}

void SoundManager::PlayBGM(int InPlayIndex, const FString& InPath, bool InIsFadeIn, float InFadeInDuration, float InFadeVolumeLevel)
{
	if (m_pBGMActorList[InPlayIndex].IsValid())
	{
		if (Load(InPath) == false)
		{
			return;
		}

		m_pBGMActorList[InPlayIndex]->PlayBGM(m_SoundMap[InPath], InIsFadeIn, InFadeInDuration, InFadeVolumeLevel);
	}
}

void SoundManager::StopBGM(int InStopIndex, bool InIsFadeOut /*= false*/, float InFadeOutDuration /*= 1.0f*/, float InFadeVolumeLevel /*= 1.0f*/)
{
	if (m_pBGMActorList[InStopIndex].IsValid())
	{
		m_pBGMActorList[InStopIndex]->StopBGM(InIsFadeOut, InFadeOutDuration, InFadeVolumeLevel);
	}
}
