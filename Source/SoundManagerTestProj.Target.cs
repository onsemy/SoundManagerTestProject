// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class SoundManagerTestProjTarget : TargetRules
{
	public SoundManagerTestProjTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "SoundManagerTestProj" } );
	}
}
