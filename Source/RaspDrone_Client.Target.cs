// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class RaspDrone_ClientTarget : TargetRules
{
	public RaspDrone_ClientTarget(TargetInfo Target) : base (Target)
	{
		Type = TargetType.Game;
        ExtraModuleNames.Add("RaspDrone_Client");
    }

}
