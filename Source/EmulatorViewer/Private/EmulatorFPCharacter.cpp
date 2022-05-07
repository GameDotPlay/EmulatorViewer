
#include "EmulatorFPCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	
	this-> OriginalWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
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

	PlayerInputComponent->BindAxis("ForwardAxis", this, &AEmulatorFPCharacter::MoveForward);
	PlayerInputComponent->BindAxis("RightAxis", this, &AEmulatorFPCharacter::StrafeRight);

	PlayerInputComponent->BindAxis("MouseX", this, &AEmulatorFPCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MouseY", this, &AEmulatorFPCharacter::AddPitch);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &AEmulatorFPCharacter::DoubleSpeed);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &AEmulatorFPCharacter::NormalSpeed);
}

void AEmulatorFPCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AEmulatorFPCharacter::StrafeRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AEmulatorFPCharacter::AddPitch(float Value)
{
	AddControllerPitchInput(-Value);
}

void AEmulatorFPCharacter::DoubleSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed *= 2;
}

void AEmulatorFPCharacter::NormalSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = this->OriginalWalkSpeed;
}