// Fill out your copyright notice in the Description page of Project Settings.

#include "BGMActor.h"
#include "Components/AudioComponent.h"


// Sets default values
ABGMActor::ABGMActor()
{
}

void ABGMActor::SetConcurrency(USoundConcurrency* InConcurrency)
{
	GetAudioComponent()->ConcurrencySettings = InConcurrency;
}

// Called when the game starts or when spawned
void ABGMActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABGMActor::PlayBGM(USoundWave* InSound, bool IsFadeIn, float InFadeInDuration, float InFadeVolumeLevel)
{
	InSound->bLooping = true;
	GetAudioComponent()->SetSound(InSound);
	
	if (IsFadeIn)
	{
		FadeIn(InFadeInDuration, InFadeVolumeLevel);
	}
	else
	{
		Play();
	}
}

void ABGMActor::StopBGM(bool InIsFadeOut, float InFadeOutDuration, float InFadeVolumeLevel)
{
	if (InIsFadeOut)
	{
		FadeOut(InFadeOutDuration, InFadeVolumeLevel);
	}
	else
	{
		Stop();
	}
}
