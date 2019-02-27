# SoundManagerTestProject
This project is managing sound control with UnrealEngine function in Unreal Engine 4.20.3 for test.

## Features

### 1. Play/Stop (Background Music, Effect)
Load `USoundWave` through Reference Path(FString), and Play or stop Audio using that.

```cpp
// Fire and forget. (a.k.a Missile)
SoundManager::GetInstance()->PlayEffect(TEXT("SoundWave'/Engine/EngineSounds/WhiteNoise.WhiteNoise'"));
```

If you want to play cross fade for BGM, use this.

```cpp
// When playing BGM already
SoundManager::GetInstance()->PlayBGM(0, TEXT("SoundWave'/Engine/EngineSounds/WhiteNoise.WhiteNoise'"), true);

// Also when playing BGM already
SoundManager::GetInstance()->StopBGM(0);
// If you want to stop with fade out, check second bool parameter
SoundManager::GetInstance()->StopBGM(0, true); // default false.
```

### 2. SetConcurrency
You can use `USoundConcurrency` for BGM or Effect. When initialized SoundManager, set concurrency polity your owns.

```cpp
void SoundManager::Initialize(UWorld* InWorld)
{
	m_pWorld = InWorld;

	m_pBGMConcurrency = LoadObject<USoundConcurrency>(nullptr, TEXT("SoundConcurrency'/path/to/BGMConcurrency.BGMConcurrency'"));
	m_pEffectConcurrency = LoadObject<USoundConcurrency>(nullptr, TEXT("SoundConcurrency'/path/to/EffectConcurrency.EffectConcurrency'"));

	m_pBGMActor = InWorld->SpawnActor<ABGMActor>();
	m_pBGMActor->SetConcurrency(m_pBGMConcurrency.Get());
	m_pBGMActor->AddToRoot();
}
```

### 3. Unload/UnloadAll
You can unload sounds if you need not it. But it is automatically unloaded when destructor called.

### 4. Preload/SetVolume [WIP]
If you want to load some sound in advance, call `Load(FString)`.
`SetVolume(float, bool, float)` is supported to *tweening*. You just check a second bool parameter.
