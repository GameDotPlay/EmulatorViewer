
#include "EmulatorCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
AEmulatorCharacter::AEmulatorCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	this->Camera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEmulatorCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEmulatorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEmulatorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AEmulatorCharacter::MoveForward);
	PlayerInputComponent->BindAxis("StrafeRight", this, &AEmulatorCharacter::StrafeRight);

	PlayerInputComponent->BindAxis("LookRight", this, &AEmulatorCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AEmulatorCharacter::AddControllerPitchInput);
}

void AEmulatorCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AEmulatorCharacter::StrafeRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}