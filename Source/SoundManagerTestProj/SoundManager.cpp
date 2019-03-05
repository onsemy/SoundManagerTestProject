// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundManager.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "AudioDevice.h"

SoundManager::SoundManager()
{
	m_nCurrentBGMIndex = 0;
}

SoundManager::~SoundManager()
{
	UnloadAll();

	m_BGMActorMap.Empty();

	m_pBGMConcurrency = nullptr;
	m_pEffectConcurrency = nullptr;
	m_pWorld = nullptr;
}

void SoundManager::Initialize(UWorld* InWorld, const FString& InBGMClass, const FString& InEffectClass, const FString& InBGMConcurrency, const FString& InEffectConcurrency, const int InMaxBGMCount)
{
	m_pWorld = InWorld;

	m_pBGMClass = LoadObject<USoundClass>(nullptr, *InBGMClass);
	m_pEffectClass = LoadObject<USoundClass>(nullptr, *InEffectClass);

	SetBGMConcurrency(InBGMConcurrency);
	SetEffectConcurrency(InEffectConcurrency);

	for (int i = 0; i < InMaxBGMCount; ++i)
	{
		ABGMActor* Actor = InWorld->SpawnActor<ABGMActor>();
		Actor->SetConcurrency(m_pBGMConcurrency.Get());

		m_BGMActorMap.Add(i, Actor);
	}
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

	m_BGMActorMap[InBGMType]->PlayBGM(m_SoundMap[InPath], InIsFadeIn, InFadeInDuration);
}

void SoundManager::StopBGM(int InBGMType, bool InIsFadeOut /*= false*/, float InFadeOutDuration /*= 1.0f*/)
{
	m_BGMActorMap[InBGMType]->StopBGM(InIsFadeOut, InFadeOutDuration);
}

void SoundManager::StopAllBGM()
{
	for (auto BGMIter(m_BGMActorMap.CreateIterator()); BGMIter; ++BGMIter)
	{
		TWeakObjectPtr<ABGMActor> BGM = BGMIter.Value();
		BGM->StopBGM();
	}
}

void SoundManager::StopAllEffect()
{
	for (auto SFXIter(m_EffectActorList.CreateIterator()); SFXIter; ++SFXIter)
	{
		TWeakObjectPtr<AEffectActor> SFX = *SFXIter;
		SFX->StopEffect();
	}
}

void SoundManager::SetBGMConcurrency(const FString& InPath)
{
	SetBGMConcurrency(LoadObject<USoundConcurrency>(nullptr, *InPath));
}

void SoundManager::SetEffectConcurrency(const FString& InPath)
{
	SetEffectConcurrency(LoadObject<USoundConcurrency>(nullptr, *InPath));
}

void SoundManager::SetBGMVolume(int InBGMType, float InVolume, bool InIsTweening, float InDuration)
{
	m_BGMActorMap[InBGMType]->SetVolume(InVolume, InIsTweening, InDuration);
}

void SoundManager::SetBGMAllVolume(float InVolume)
{
	if (m_pBGMClass.IsValid())
	{
		m_pBGMClass->Properties.Volume = InVolume;
	}
}

void SoundManager::SetEffectAllVolume(float InVolume)
{
	if (m_pEffectClass.IsValid())
	{
		m_pEffectClass->Properties.Volume = InVolume;
	}
}

void SoundManager::SetMute(bool InIsMute)
{
	if (FAudioDevice* Device = GEngine->GetMainAudioDevice())
	{
		Device->SetDeviceMuted(InIsMute);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AudioDevice is not found!"));
	}
}

