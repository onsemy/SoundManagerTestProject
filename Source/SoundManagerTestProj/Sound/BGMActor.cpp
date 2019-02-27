// Fill out your copyright notice in the Description page of Project Settings.

#include "BGMActor.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

ABGMActor::ABGMActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABGMActor::SetConcurrency(USoundConcurrency* InConcurrency)
{
	m_pSoundConcurrency = InConcurrency;
}

void ABGMActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (auto MapIter = m_AudioComponentMap.CreateIterator(); MapIter; ++MapIter)
	{
		for (auto CompIter = MapIter.Value().CreateIterator(); CompIter; ++CompIter)
		{
			TWeakObjectPtr<UAudioComponent> Comp = *CompIter;
			Comp->RemoveFromRoot();
			Comp = nullptr;
		}
		MapIter.Value().Empty();
	}
	m_AudioComponentMap.Empty();

	Super::EndPlay(EndPlayReason);
}

void ABGMActor::Tick(float DeltaSeconds)
{
	if (IsVolumeTweening)
	{
		// TODO(JJO): tweening volume
		//
	}
}

void ABGMActor::PlayBGM(int InBGMType, USoundWave* InSound, bool InIsCrossFade, float InCrossFadeDuration)
{
	InSound->bLooping = true;
	if (m_AudioComponentMap.Contains(InBGMType) == false)
	{
		TArray<TWeakObjectPtr<UAudioComponent>> ComponentArray;
		// NOTE(JJO): For cross fade (swap)
		for (int i = 0; i < 2; ++i)
		{
			UAudioComponent* AudioComponent = UGameplayStatics::CreateSound2D(GetWorld(), InSound, 1.0f, 1.0f, 0.0f, m_pSoundConcurrency.Get(), false, false);
			AudioComponent->AddToRoot();
			ComponentArray.Add(AudioComponent);
		}
		m_AudioComponentMap.Add(InBGMType, ComponentArray);
	}

	PlayBGM_Internal(InBGMType, InSound, InIsCrossFade, InCrossFadeDuration);
}

void ABGMActor::StopBGM(int InBGMType, bool InIsFadeOut, float InFadeOutDuration)
{
	if (m_AudioComponentMap.Contains(InBGMType) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find audio component - %d"), InBGMType);
		return;
	}

	StopBGM_Internal(InBGMType, InIsFadeOut, InFadeOutDuration);
}

bool ABGMActor::IsPlaying(int InBGMType)
{
	if (m_AudioComponentMap.Contains(InBGMType) == false)
	{
		return false;
	}

	for (auto CompIter = m_AudioComponentMap[InBGMType].CreateIterator(); CompIter; ++CompIter)
	{
		TWeakObjectPtr<UAudioComponent> Comp = *CompIter;
		if (Comp->IsPlaying())
		{
			return true;
		}
	}

	return false;
}

void ABGMActor::PlayBGM_Internal(int InBGMType, USoundWave* InSound, bool InIsCrossFade /*= false*/, float InCrossFadeDuration /*= 1.0f*/)
{
	for (auto CompIter = m_AudioComponentMap[InBGMType].CreateIterator(); CompIter; ++CompIter)
	{
		TWeakObjectPtr<UAudioComponent> Comp = *CompIter;
		if (InIsCrossFade)
		{
			if (Comp->IsPlaying() == false)
			{
				Comp->FadeIn(InCrossFadeDuration);
			}
			else
			{
				Comp->FadeOut(InCrossFadeDuration, 1.0f);
			}
		}
		else
		{
			Comp->Play();
			break;
		}
	}
}

void ABGMActor::StopBGM_Internal(int InBGMType, bool InIsFadeOut /*= false*/, float InFadeOutDuration /*= 1.0f*/)
{
	for (auto CompIter = m_AudioComponentMap[InBGMType].CreateIterator(); CompIter; ++CompIter)
	{
		TWeakObjectPtr<UAudioComponent> Comp = *CompIter;
		if (InIsFadeOut)
		{
			if (Comp->IsPlaying())
			{
				Comp->FadeOut(InFadeOutDuration, 1.0f);
			}
		}
		else
		{
			Comp->Stop();
			break;
		}
	}
}
