# SoundManagerTestProject
This project is managing sound control with UnrealEngine function in Unreal Engine 4.20.3 for test.

## Features

### 1. Load/Play/Stop (Background Music, Effect)
Load `USoundWave` through Reference Path(FString), and Play or stop Audio using that.

```cpp
SoundManager::GetInstance()->PlayEffect(TEXT("SoundWave'/Engine/EngineSounds/WhiteNoise.WhiteNoise'"));
```

If you want to cross fade, use this.

```cpp
SoundManager::GetInstance()->StopBGM(true);
SoundManager::GetInstance()->PlayEffect(TEXT("SoundWave'/Engine/EngineSounds/WhiteNoise.WhiteNoise'"), true);
```

### 2. SetConcurrency
You can use `USoundConcurrency` for BGM or Effect. When initialized SoundManager, set concurrency polity your owns.

```cpp
void SoundManager::Initialize(UWorld* InWorld)
{
	m_pWorld = InWorld;

	// NOTE(JJO): For example.
	m_pBGMConcurrency = LoadObject<USoundConcurrency>(nullptr, TEXT("SoundConcurrency'/Game/Sound/NewSoundConcurrency.NewSoundConcurrency'"));
	m_pEffectConcurrency = LoadObject<USoundConcurrency>(nullptr, TEXT("SoundConcurrency'/Game/Sound/NewSoundConcurrency.NewSoundConcurrency'"));

	for (int i = 0; i < 2; ++i)
	{
		ABGMActor* Actor = InWorld->SpawnActor<ABGMActor>();
		Actor->SetConcurrency(m_pBGMConcurrency.Get());
		Actor->AddToRoot();
		m_pBGMActorList.Add(Actor);
	}
}
```

### 3. Unload/UnloadAll
You can unload sounds if you need not it.

### 4. Preload/SetVolume [WIP]
If you want to load some sound in advance, call `Preload(FString)`.
