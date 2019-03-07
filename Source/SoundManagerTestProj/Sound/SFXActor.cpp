// Fill out your copyright notice in the Description page of Project Settings.

#include "SFXActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "SoundManager.h"


// Sets default values
ASFXActor::ASFXActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_pAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	RootComponent = m_pAudioComponent.Get();

	m_pAudioComponent->OnAudioFinished.AddDynamic(this, &ASFXActor::OnAudioFinished);
}

void ASFXActor::PlayEffect(USoundWave* InSound, float InVolume)
{
	if (m_pAudioComponent->IsPlaying())
	{
		// NOTE(JJO): remove reference count of previous version
		AudioFinishedDelegate.Broadcast(m_pSoundWave.Get());
	}

	m_pSoundWave = InSound;


	m_pAudioComponent->ConcurrencySettings = m_pSoundConcurrency.Get();
	m_pAudioComponent->SetSound(m_pSoundWave.Get());
	m_pAudioComponent->VolumeMultiplier = InVolume;

	if (m_pAudioComponent->IsPlaying() == false)
	{
		m_pAudioComponent->Play();
	}
}

void ASFXActor::StopEffect()
{
	if (m_pAudioComponent.IsValid() &&
		m_pAudioComponent->IsPlaying())
	{
		m_pAudioComponent->Stop();

		// NOTE(JJO): I don't know why didn't called OnAudioFinished
		OnAudioFinished();
	}
}

void ASFXActor::OnAudioFinished()
{
	AudioFinishedDelegate.Broadcast(m_pSoundWave.Get());

	m_pAudioComponent->SetSound(nullptr);
	m_pSoundWave = nullptr;
}

