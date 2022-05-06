
#include "EmulatorFPCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
AEmulatorFPCharacter::AEmulatorFPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	this->Camera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEmulatorFPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEmulatorFPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEmulatorFPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AEmulatorFPCharacter::MoveForward);
	PlayerInputComponent->BindAxis("StrafeRight", this, &AEmulatorFPCharacter::StrafeRight);

	PlayerInputComponent->BindAxis("LookRight", this, &AEmulatorFPCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AEmulatorFPCharacter::AddControllerPitchInput);
}

void AEmulatorFPCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AEmulatorFPCharacter::StrafeRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}