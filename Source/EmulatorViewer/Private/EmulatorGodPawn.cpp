
#include "EmulatorGodPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EmulatorPlayerController.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"

// Sets default values
AEmulatorGodPawn::AEmulatorGodPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->LookTarget = CreateDefaultSubobject<USphereComponent>("LookTarget");
	this->SetRootComponent(this->LookTarget);

	this->SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	this->SpringArm->SetupAttachment(this->RootComponent);

	this->Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	this->Camera->SetupAttachment(this->SpringArm);
}

// Called when the game starts or when spawned
void AEmulatorGodPawn::BeginPlay()
{
	Super::BeginPlay();

	this->PlayerController = Cast<APlayerController>(GetController());
	check(this->PlayerController);

	this->PlayerController->GetViewportSize(this->CurrentViewportSize.X, this->CurrentViewportSize.Y);
}

// Called every frame
void AEmulatorGodPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	check(this->PlayerController);
	this->PlayerController->GetMousePosition(this->MousePosition.X, this->MousePosition.Y);

	if (this->bMouseEdgeScrollEnabled && !this->bMiddleMousePressed)
	{
		this->MouseEdgeScroll();
	}
}

void AEmulatorGodPawn::MouseEdgeScroll()
{
	if (this->MousePosition.X > this->CurrentViewportSize.X - this->ScreenEdgeBuffer)
	{
		this->MoveRight(1.f);
	}

	if (this->MousePosition.Y > this->CurrentViewportSize.Y - this->ScreenEdgeBuffer)
	{
		this->MoveForward(-1.f);
	}

	if (this->MousePosition.X < this->ScreenEdgeBuffer)
	{
		this->MoveRight(-1.f);
	}

	if (this->MousePosition.Y < this->ScreenEdgeBuffer)
	{
		this->MoveForward(1.f);
	}
}

void AEmulatorGodPawn::MoveForward(float Value)
{
	float PreviousZ = GetActorLocation().Z;
	float DeltaSeconds = GetWorld()->GetDeltaSeconds();
	FVector DeltaLocation = FVector(GetActorForwardVector() * Value * this->MouseEdgeScrollSpeed * DeltaSeconds);
	AddActorWorldOffset(DeltaLocation);
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, PreviousZ));
}

void AEmulatorGodPawn::MoveRight(float Value)
{
	float PreviousZ = GetActorLocation().Z;
	float DeltaSeconds = GetWorld()->GetDeltaSeconds();
	FVector DeltaLocation = FVector(GetActorRightVector() * Value * this->MouseEdgeScrollSpeed * DeltaSeconds);
	AddActorWorldOffset(DeltaLocation);
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, PreviousZ));
}

void AEmulatorGodPawn::MiddleMousePressed()
{
	this->bMiddleMousePressed = true;
}

void AEmulatorGodPawn::MiddleMouseReleased()
{
	this->bMiddleMousePressed = false;
}

void AEmulatorGodPawn::KeyboardF(FVector Location)
{
	this->FocusView(Location);
}

void AEmulatorGodPawn::KeyboardEND(float NewZ)
{
	this->SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, NewZ));
}

void AEmulatorGodPawn::MouseXAxis(float Value)
{
	if (this->bMiddleMousePressed)
	{
		if (this->bInvertMouseX)
		{
			Value = -Value;
		}

		FQuat DeltaRotation = FRotator(0.f, Value * MouseRotateSpeed * GetWorld()->GetDeltaSeconds(), 0.f).Quaternion();
		AddActorLocalRotation(DeltaRotation);
		SetActorRelativeRotation(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, 0.f));
	}
}

void AEmulatorGodPawn::MouseYAxis(float Value)
{
	if (this->bMiddleMousePressed)
	{
		if (this->bInvertMouseY)
		{
			Value = -Value;
		}

		FQuat DeltaRotation = FRotator(Value * MouseRotateSpeed * GetWorld()->GetDeltaSeconds(), 0.f, 0.f).Quaternion();
		AddActorLocalRotation(DeltaRotation);
		SetActorRelativeRotation(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, 0.f));

		if (GetActorRotation().Pitch > this->MaxPitchValue)
		{
			SetActorRelativeRotation(FRotator(this->MaxPitchValue, GetActorRotation().Yaw, GetActorRotation().Roll));
		}
		else if (GetActorRotation().Pitch < this->MinPitchValue)
		{
			SetActorRelativeRotation(FRotator(this->MinPitchValue, GetActorRotation().Yaw, GetActorRotation().Roll));
		}
	}
}

void AEmulatorGodPawn::MouseWheelAxis(float Value)
{
	this->Zoom(Value);
}

void AEmulatorGodPawn::FocusView(FVector Location)
{
	this->SetActorLocation(Location);
}

void AEmulatorGodPawn::Zoom(float Value)
{
	this->SpringArm->TargetArmLength -= Value * GetWorld()->GetDeltaSeconds() * this->MouseWheelSensitivity;

	if (this->SpringArm->TargetArmLength < MinTargetArmLength)
	{
		this->SpringArm->TargetArmLength = this->MinTargetArmLength;
	}
	else if (this->SpringArm->TargetArmLength > MaxTargetArmLength)
	{
		this->SpringArm->TargetArmLength = this->MaxTargetArmLength;
	}
}