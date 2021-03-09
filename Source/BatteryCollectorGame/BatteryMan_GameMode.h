// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"


#include "BatteryMan_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYCOLLECTORGAME_API ABatteryMan_GameMode : public AGameMode
{
	GENERATED_BODY()
	ABatteryMan_GameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn>  PlayerRecharge;

	float FSpawn_Z =  500.0f;

	UPROPERTY(EditAnywhere)
	float FSpawn_X_Min;
	
	UPROPERTY(EditAnywhere)
	float FSpawn_X_Max;

	UPROPERTY(EditAnywhere)
	float FSpawn_Y_Min;
	
	UPROPERTY(EditAnywhere)
	float FSpawn_Y_Max;

	void SpawnPlayerRecharge(); 
	
	
};
