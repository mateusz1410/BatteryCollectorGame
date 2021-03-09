// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryMan_GameMode.h"
#include "GameFramework/Actor.h"

ABatteryMan_GameMode::ABatteryMan_GameMode()
{
	PrimaryActorTick.bCanEverTick=true;
}

void ABatteryMan_GameMode::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle,this,&ABatteryMan_GameMode::SpawnPlayerRecharge,FMath::RandRange(2,5),true); //Set Timer by Event
	
}
void ABatteryMan_GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABatteryMan_GameMode::SpawnPlayerRecharge()
{
	float RandX=FMath::RandRange(FSpawn_X_Min,FSpawn_X_Max);
	float RandY=FMath::RandRange(FSpawn_Y_Min,FSpawn_Y_Max);
	
	FVector SpawnPosition = FVector(RandX,RandY,FSpawn_Z);
	FRotator SpawnRotation = FRotator(0.0f,0.0f,0.0f);

	GetWorld()->SpawnActor(PlayerRecharge,&SpawnPosition,&SpawnRotation);
	
}


