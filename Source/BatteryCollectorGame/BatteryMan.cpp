// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryMan.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

#include <string>


#include "Chaos/GeometryParticlesfwd.h"

// Sets default values
ABatteryMan::ABatteryMan()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleRadius(42.0f,96.0f);
	
	bUseControllerRotationPitch = false; // character doesn't rotate with camera
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement=true;
	GetCharacterMovement()->RotationRate=FRotator(0.0f,540.0f,0.0f); //strength of rotate, how fast
	GetCharacterMovement()->JumpZVelocity=600.0f;
	GetCharacterMovement()->AirControl=0.2f;
	
	CameraBoom=CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength=300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera=CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation=false;

	bDead = false;
	FPower = 100.0f;
	FPower_Treshold= 5.0f;
}


// Called when the game starts or when spawned
void ABatteryMan::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&ABatteryMan::OnBeginOverlap);

	if(WDG_Power_Class != nullptr)
	{
		WDG_Power_Widget=CreateWidget(GetWorld(),WDG_Power_Class);
		WDG_Power_Widget->AddToViewport();
	}
}

// Called every frame
void ABatteryMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FPower-=DeltaTime*FPower_Treshold;
	
	if(FPower<0)
	{
		if(!bDead)
		{
			bDead=true;
			GetMesh()->SetSimulatePhysics(true);
			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(UnusedHandle,this,&ABatteryMan::RestartGame,3.0f,false); //Set Timer by Event
		}
	}

}

// Called to bind functionality to input
void ABatteryMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward",this,&ABatteryMan::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ABatteryMan::MoveRight);
}

void ABatteryMan::MoveForward(float Axis)
{
	if(!bDead)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator  YawRotation(0.0f,Rotation.Yaw,0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction,Axis);
	}
}

void ABatteryMan::MoveRight(float Axis)
{
	if(!bDead)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f,Rotation.Yaw,0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction,Axis);
	}
}


void ABatteryMan::RestartGame() //restart game
{
	UGameplayStatics::OpenLevel(this,FName(*GetWorld()->GetName()),false);
}


void ABatteryMan::OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Recharge"))
	{
		//UE_LOG(LogTemp,Warning, TEXT("Collided With")); //add to outputLog
		FPower+=30.0f;
		
		if(FPower>100.0f)
			FPower=100.0f;

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(FPower));
		OtherActor->Destroy();
		
	}
}