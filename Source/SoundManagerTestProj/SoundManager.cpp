// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundManager.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "AudioDevice.h"
#include "Sound/EffectActor.h"

SoundManager::SoundManager()
{
	m_nCurrentBGMIndex = 0;
}

SoundManager::~SoundManager()
{
	UnloadAll();

	m_BGMActorMap.Empty();

	m_EffectActorList.Empty();

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

	m_nEffectMaxCount = m_pEffectConcurrency.IsValid() ? m_pEffectConcurrency->Concurrency.MaxCount : 50;
	for (int i = 0; i < m_nEffectMaxCount; ++i)
	{
		AEffectActor* Actor = InWorld->SpawnActor<AEffectActor>();

		m_EffectActorList.Add(Actor);
	}

	m_nCurrentEffectIndex = 0;
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
	//if (FAudioDevice* Device = GEngine->GetActiveAudioDevice())
	//{
	//	if (Device->IsAudioDeviceMuted())
	//	{
	//		return;
	//	}
	//}
	if (m_bIsMute)
	{
		return;
	}

	if (Load(InPath) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to PlayEffect - %s is invalid"), *InPath);
		return;
	}

	m_SoundMap[InPath]->bLooping = false;
	m_EffectActorList[m_nCurrentEffectIndex]->PlayEffect(m_SoundMap[InPath]);
	m_nCurrentEffectIndex = (m_nCurrentEffectIndex + 1) % m_nEffectMaxCount;
}

void SoundManager::PlayBGM(int InBGMType, const FString& InPath, bool InIsFadeIn, float InFadeInDuration)
{
	//if (FAudioDevice* Device = GEngine->GetActiveAudioDevice())
	//{
	//	if (Device->IsAudioDeviceMuted())
	//	{
	//		return;
	//	}
	//}
	if (m_bIsMute)
	{
		return;
	}

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
	m_bIsMute = InIsMute;
	if (FAudioDevice* Device = GEngine->GetActiveAudioDevice())
	{
		Device->SetDeviceMuted(InIsMute);
		StopAllEffect();
		StopAllBGM();

		UnloadAll();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AudioDevice is not found!"));
	}

	OnMutedDelegate.Broadcast(m_bIsMute);
}

int SoundManager::AddReferenceCount(USoundWave* InSound)
{
	if (m_SoundReferenceMap.Contains(InSound) == false)
	{
		m_SoundReferenceMap.Add(InSound, 0);
	}

	m_SoundReferenceMap[InSound]++;

	UE_LOG(LogTemp, Log, TEXT("%s ref count: %d"), *InSound->GetName(), m_SoundReferenceMap[InSound]);

	return m_SoundReferenceMap[InSound];
}

int SoundManager::RemoveReferenceCount(USoundWave* InSound)
{
	if (m_SoundReferenceMap.Contains(InSound) == false)
	{
		return 0;
	}

	m_SoundReferenceMap[InSound]--;
	UE_LOG(LogTemp, Log, TEXT("%s ref count: %d"), *InSound->GetName(), m_SoundReferenceMap[InSound]);
	if (m_SoundReferenceMap[InSound] == 0)
	{
		m_SoundReferenceMap.Remove(InSound);
		for (auto SoundIter(m_SoundMap.CreateIterator()); SoundIter; ++SoundIter)
		{
			USoundWave* Sound = SoundIter.Value();
			if (Sound == InSound)
			{
				m_SoundMap.Remove(SoundIter.Key());

				return 0;
			}
		}
	}

	return m_SoundReferenceMap[InSound];
}

