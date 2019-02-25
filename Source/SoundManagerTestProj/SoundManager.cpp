// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundManager.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
	m_SoundMap.Empty();
	m_pBGMActor = nullptr;
	m_pConcurrency = nullptr;
	m_pWorld = nullptr;
}

void SoundManager::Initialize(UWorld* InWorld)
{
	m_pWorld = InWorld;

	for (TActorIterator<ABGMActor> ActorIter(InWorld); ActorIter; ++ActorIter)
	{
		ABGMActor* Sound = *ActorIter;
		//if (Sound->GetName().Equals(TEXT("bgm")))
		{
			m_pBGMActor = Sound;
			break;
		}
	}

	m_pConcurrency = LoadObject<USoundConcurrency>(nullptr, TEXT("SoundConcurrency'/Game/Sound/NewSoundConcurrency.NewSoundConcurrency'"));
}

bool SoundManager::Load(const FString& InPath)
{
	if (m_SoundMap.Contains(InPath) == false)
	{
		USoundBase* Sound = LoadObject<USoundBase>(nullptr, *InPath);
		if (Sound == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load sound - %s"), *InPath);
			return false;
		}

		m_SoundMap.Add(InPath, Sound);
	}

	return true;
}

void SoundManager::PlayEffect(const FString& InPath)
{
	if (Load(InPath) == false)
	{
		return;
	}

	UGameplayStatics::PlaySound2D(GetWorld(), m_SoundMap[InPath], 1.0f, 1.0f, 0.0f, m_pConcurrency.Get());
}

void SoundManager::PlayBGM(const FString& InPath, bool InIsFadeIn, float InFadeInDuration, float InFadeVolumeLevel)
{
	if (m_pBGMActor.IsValid())
	{
		if (Load(InPath) == false)
		{
			return;
		}

		m_pBGMActor->PlayBGM(m_SoundMap[InPath], InIsFadeIn, InFadeInDuration, InFadeVolumeLevel);
		//UGameplayStatics::PlaySound2D(GetWorld(), m_SoundMap[InPath], 1.0f, 1.0f, 0.0f, m_pConcurrency.Get(), m_pBGMActor.Get());
	}
}

void SoundManager::StopBGM(bool InIsFadeOut /*= false*/, float InFadeOutDuration /*= 1.0f*/, float InFadeVolumeLevel /*= 1.0f*/)
{
	if (m_pBGMActor.IsValid())
	{
		m_pBGMActor->StopBGM(InIsFadeOut, InFadeOutDuration, InFadeVolumeLevel);
	}
}
