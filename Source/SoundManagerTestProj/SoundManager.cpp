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
	UnloadAll();

	m_pBGMActor->RemoveFromRoot();
	m_pBGMActor = nullptr;

	m_pBGMConcurrency = nullptr;
	m_pEffectConcurrency = nullptr;
	m_pWorld = nullptr;
}

void SoundManager::Initialize(UWorld* InWorld)
{
	m_pWorld = InWorld;

	m_pBGMConcurrency = LoadObject<USoundConcurrency>(nullptr, TEXT("SoundConcurrency'/Game/Sound/BGMConcurrency.BGMConcurrency'"));
	m_pEffectConcurrency = LoadObject<USoundConcurrency>(nullptr, TEXT("SoundConcurrency'/Game/Sound/NewSoundConcurrency.NewSoundConcurrency'"));

	m_pBGMActor = InWorld->SpawnActor<ABGMActor>();
	m_pBGMActor->SetConcurrency(m_pBGMConcurrency.Get());
	m_pBGMActor->AddToRoot();
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
		Sound->AddToRoot();

		m_SoundMap.Add(InPath, Sound);
	}

	return true;
}

void SoundManager::UnloadAll()
{
	for (auto SoundIter = m_SoundMap.CreateIterator(); SoundIter; ++SoundIter)
	{
		USoundWave* Wave = SoundIter.Value();
		Wave->RemoveFromRoot();
	}

	m_SoundMap.Empty();
}

void SoundManager::PlayEffect(const FString& InPath)
{
	if (Load(InPath) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to PlayEffect - %s is invalid"), *InPath);
		return;
	}

	m_SoundMap[InPath]->bLooping = false;
	UGameplayStatics::PlaySound2D(GetWorld(), m_SoundMap[InPath], 1.0f, 1.0f, 0.0f, m_pEffectConcurrency.Get());
}

void SoundManager::PlayBGM(int InBGMType, const FString& InPath, bool InIsFadeIn, float InFadeInDuration)
{
	if (Load(InPath) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to PlayBGM - %s is invalid"), *InPath);
		return;
	}

	m_pBGMActor->PlayBGM(InBGMType, m_SoundMap[InPath], InIsFadeIn, InFadeInDuration);
}

void SoundManager::StopBGM(int InBGMType, bool InIsFadeOut /*= false*/, float InFadeOutDuration /*= 1.0f*/)
{
	m_pBGMActor->StopBGM(InBGMType, InIsFadeOut, InFadeOutDuration);
}
