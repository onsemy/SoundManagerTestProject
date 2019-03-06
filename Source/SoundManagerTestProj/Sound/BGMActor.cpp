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
	for (auto CompIter = m_AudioComponentList.CreateIterator(); CompIter; ++CompIter)
	{
		TWeakObjectPtr<UAudioComponent> Comp = *CompIter;
		Comp->RemoveFromRoot();
		Comp = nullptr;
	}

	m_AudioComponentList.Empty();

	Super::EndPlay(EndPlayReason);
}

void ABGMActor::Tick(float DeltaSeconds)
{
	if (m_bIsVolumeTweening)
	{
		// TODO(JJO): tweening volume
		//
		m_fCurrentDuration += DeltaSeconds;
		if (m_fCurrentDuration >= m_fTargetDuration)
		{
			m_fCurrentDuration = m_fTargetDuration;
			m_bIsVolumeTweening = false;
		}

		for (auto CompIter = m_AudioComponentList.CreateIterator(); CompIter; ++CompIter)
		{
			TWeakObjectPtr<UAudioComponent> Comp = *CompIter;
			Comp->VolumeMultiplier = FMath::Lerp(m_fOriginVolume, m_fTargetVolume, m_fCurrentDuration);
		}
	}
}

void ABGMActor::PlayBGM(USoundWave* InSound, bool InIsCrossFade, float InCrossFadeDuration)
{
	InSound->bLooping = true;
	if (m_AudioComponentList.Num() == 0)
	{
		// NOTE(JJO): For cross fade (swap)
		for (int i = 0; i < 2; ++i)
		{
			UAudioComponent* AudioComponent = UGameplayStatics::CreateSound2D(GetWorld(), InSound, 1.0f, 1.0f, 0.0f, m_pSoundConcurrency.Get(), false, false);
			AudioComponent->AddToRoot();
			m_AudioComponentList.Add(AudioComponent);
		}
	}

	PlayBGM_Internal(InSound, InIsCrossFade, InCrossFadeDuration);
}

void ABGMActor::StopBGM(bool InIsFadeOut, float InFadeOutDuration)
{
	StopBGM_Internal(InIsFadeOut, InFadeOutDuration);
}

bool ABGMActor::IsPlaying()
{
	for (auto CompIter = m_AudioComponentList.CreateIterator(); CompIter; ++CompIter)
	{
		TWeakObjectPtr<UAudioComponent> Comp = *CompIter;
		if (Comp->IsPlaying())
		{
			return true;
		}
	}

	return false;
}

void ABGMActor::SetVolume(float InVolume, bool InIsTweening /*= false*/, float InDuration)
{
	m_fTargetVolume = InVolume;

	if (InIsTweening)
	{
		m_fOriginVolume = m_AudioComponentList[0]->VolumeMultiplier;

		m_fTargetDuration = InDuration;
		m_fCurrentDuration = 0.0f;
	}
	else
	{
		m_fOriginVolume = InVolume;

		m_fTargetDuration = InDuration;
		m_fCurrentDuration = InDuration;

		m_AudioComponentList[0]->VolumeMultiplier = InVolume;
		m_AudioComponentList[1]->VolumeMultiplier = InVolume;
	}

	m_bIsVolumeTweening = InIsTweening;
}

void ABGMActor::PlayBGM_Internal(USoundWave* InSound, bool InIsCrossFade /*= false*/, float InCrossFadeDuration /*= 1.0f*/)
{
	bool IsAlreadyFadeIn = false;
	bool IsAlreadyFadeOut = false;
	for (auto CompIter = m_AudioComponentList.CreateIterator(); CompIter; ++CompIter)
	{
		TWeakObjectPtr<UAudioComponent> Comp = *CompIter;
		if (InIsCrossFade)
		{
			if (Comp->IsPlaying() == false)
			{
				// NOTE(JJO): For first called PlayBGM
				if (IsAlreadyFadeIn == false)
				{
					Comp->SetSound(InSound);
					Comp->FadeIn(InCrossFadeDuration);
					IsAlreadyFadeIn = true;
				}
			}
			else
			{
				if (IsAlreadyFadeOut == false)
				{
					Comp->FadeOut(InCrossFadeDuration, 0.0f);
					IsAlreadyFadeOut = true;
				}
			}
		}
		else
		{
			if (IsAlreadyFadeIn == false)
			{
				Comp->SetSound(InSound);
				Comp->Play();
				IsAlreadyFadeIn = true;
			}
			else
			{
				Comp->Stop();
			}
		}
	}

	m_pCurrentSound = InSound;
}

void ABGMActor::StopBGM_Internal(bool InIsFadeOut /*= false*/, float InFadeOutDuration /*= 1.0f*/)
{
	for (auto CompIter = m_AudioComponentList.CreateIterator(); CompIter; ++CompIter)
	{
		TWeakObjectPtr<UAudioComponent> Comp = *CompIter;
		if (InIsFadeOut)
		{
			if (Comp->IsPlaying())
			{
				Comp->FadeOut(InFadeOutDuration, 0.0f);
			}
		}
		else
		{
			Comp->Stop();
		}
	}

	m_pCurrentSound = nullptr;
}
