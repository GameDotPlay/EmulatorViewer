
#include "EmulatorGodPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EmulatorPlayerController.h"
#include "DrawDebugHelpers.h"

// Sets default values
AEmulatorGodPawn::AEmulatorGodPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->LookTarget = CreateDefaultSubobject<USceneComponent>("LookTarget");
	this->SetRootComponent(this->LookTarget);

	this->SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	this->SpringArm->SetupAttachment(this->LookTarget);

	this->Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	this->Camera->SetupAttachment(this->SpringArm);
}

// Called when the game starts or when spawned
void AEmulatorGodPawn::BeginPlay()
{
	Super::BeginPlay();

	this->PlayerController = Cast<AEmulatorPlayerController>(GetController());
	check(this->PlayerController);
	this->PlayerController->GetViewportSize(this->CurrentViewportSize.X, this->CurrentViewportSize.Y);
}

// Called every frame
void AEmulatorGodPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	check(this->PlayerController);
	this->PlayerController->GetMousePosition(this->MousePosition.X, this->MousePosition.Y);

	DrawDebugDirectionalArrow(GetWorld(), GetActorLocation() + FVector(0, 0, 100.f), GetActorLocation() + GetActorForwardVector() * 100.f, 10.f, FColor::Red, false, -1.f, 0, 5.f);

	this->MouseEdgeScroll();
}

// Called to bind functionality to input
void AEmulatorGodPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MouseWheel", this, &AEmulatorGodPawn::Zoom);
	PlayerInputComponent->BindAxis("MouseX", this, &AEmulatorGodPawn::RotateMouseX);
	PlayerInputComponent->BindAxis("MouseY", this, &AEmulatorGodPawn::RotateMouseY);

	PlayerInputComponent->BindAction("MiddleMouseButton", EInputEvent::IE_Pressed, this, &AEmulatorGodPawn::MiddleMousePressed);
	PlayerInputComponent->BindAction("MiddleMouseButton", EInputEvent::IE_Released, this, &AEmulatorGodPawn::MiddleMouseReleased);
	PlayerInputComponent->BindAction("KeyboardF", EInputEvent::IE_Pressed, this, &AEmulatorGodPawn::FocusView);
}

void AEmulatorGodPawn::MouseEdgeScroll()
{
	float PreviousZ = GetActorLocation().Z;
	if (this->MousePosition.X > this->CurrentViewportSize.X - this->ScreenEdgeBuffer)
	{
		FVector RightVector = GetActorRightVector();
		AddActorLocalOffset(RightVector * this->MouseEdgeScrollSpeed);
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, PreviousZ));
	}

	if (this->MousePosition.Y > this->CurrentViewportSize.Y - this->ScreenEdgeBuffer)
	{
		FVector ForwardVector = GetActorForwardVector();
		ForwardVector.RotateAngleAxis(-GetActorRotation().Pitch, GetActorRightVector()).Normalize();
		AddActorLocalOffset(-ForwardVector * this->MouseEdgeScrollSpeed);
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, PreviousZ));
	}

	if (this->MousePosition.X < this->ScreenEdgeBuffer)
	{
		FVector RightVector = GetActorRightVector();
		AddActorLocalOffset(-RightVector * this->MouseEdgeScrollSpeed);
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, PreviousZ));
	}

	if (this->MousePosition.Y < this->ScreenEdgeBuffer)
	{
		FVector ForwardVector = GetActorForwardVector();
		ForwardVector.RotateAngleAxis(-GetActorRotation().Pitch, GetActorRightVector()).Normalize();
		AddActorLocalOffset(ForwardVector * this->MouseEdgeScrollSpeed);
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, PreviousZ));
	}
}

void AEmulatorGodPawn::MiddleMousePressed()
{
	this->bMiddleMousePressed = true;
}

void AEmulatorGodPawn::MiddleMouseReleased()
{
	this->bMiddleMousePressed = false;
}

void AEmulatorGodPawn::RotateMouseX(float Value)
{
	if (this->bMiddleMousePressed)
	{
		if (this->bInvertMouseX)
		{
			Value = -Value;
		}

		AddActorLocalRotation(FRotator(0.f, Value * MouseRotateSpeed, 0.f).Quaternion());
		SetActorRelativeRotation(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, 0.f));
	}
}

void AEmulatorGodPawn::RotateMouseY(float Value)
{
	if (this->bMiddleMousePressed)
	{
		if (this->bInvertMouseY)
		{
			Value = -Value;
		}

		AddActorLocalRotation(FRotator(Value * MouseRotateSpeed, 0.f, 0.f).Quaternion());
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

void AEmulatorGodPawn::FocusView()
{

}

void AEmulatorGodPawn::Zoom(float Value)
{
	this->SpringArm->TargetArmLength -= Value * this->MouseWheelSensitivity;

	if (this->SpringArm->TargetArmLength < MinTargetArmLength)
	{
		this->SpringArm->TargetArmLength = this->MinTargetArmLength;
	}
	else if (this->SpringArm->TargetArmLength > MaxTargetArmLength)
	{
		this->SpringArm->TargetArmLength = this->MaxTargetArmLength;
	}
}