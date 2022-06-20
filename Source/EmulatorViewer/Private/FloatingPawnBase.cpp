


#include "FloatingPawnBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "EmulatorPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFloatingPawnBase::AFloatingPawnBase()
{
	PrimaryActorTick.bCanEverTick = true;

	this->LookTarget = CreateDefaultSubobject<USphereComponent>("LookTarget");
	this->SetRootComponent(this->LookTarget);

	this->SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	this->SpringArm->SetupAttachment(this->RootComponent);

	this->Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	this->Camera->SetupAttachment(this->SpringArm);
}

void AFloatingPawnBase::BeginPlay()
{
	Super::BeginPlay();

	this->PlayerController = Cast<AEmulatorPlayerController>(GetWorld()->GetFirstPlayerController());
	check(this->PlayerController);

	this->PlayerController->GetViewportSize(this->CurrentViewportSize.X, this->CurrentViewportSize.Y);

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(this, FName(TEXT("Floor")), Actors);
	check(Actors.Num() > 0);
	this->FloorZ = Actors[0]->GetActorLocation().Z;
}

void AFloatingPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	check(this->PlayerController);
	this->PlayerController->GetMousePosition(this->MousePosition.X, this->MousePosition.Y);

	if (this->bMouseEdgeScrollEnabled && !this->bMiddleMouseDown)
	{
		this->MouseEdgeScroll();
	}
}

void AFloatingPawnBase::MouseEdgeScroll()
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

void AFloatingPawnBase::MoveForward(float Value)
{
	float PreviousZ = GetActorLocation().Z;
	float DeltaSeconds = GetWorld()->GetDeltaSeconds();
	FVector DeltaLocation = FVector(GetActorForwardVector() * Value * this->MouseEdgeScrollSpeed * DeltaSeconds);
	AddActorWorldOffset(DeltaLocation);
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, PreviousZ));
}

void AFloatingPawnBase::MoveRight(float Value)
{
	float PreviousZ = GetActorLocation().Z;
	float DeltaSeconds = GetWorld()->GetDeltaSeconds();
	FVector DeltaLocation = FVector(GetActorRightVector() * Value * this->MouseEdgeScrollSpeed * DeltaSeconds);
	AddActorWorldOffset(DeltaLocation);
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, PreviousZ));
}

void AFloatingPawnBase::MoveUp(float Value)
{
	float PreviousX = GetActorLocation().X;
	float PreviousY = GetActorLocation().Y;
	float DeltaSeconds = GetWorld()->GetDeltaSeconds();
	FVector DeltaLocation = FVector(GetActorUpVector() * Value * this->MouseEdgeScrollSpeed * DeltaSeconds);
	AddActorWorldOffset(DeltaLocation);
	SetActorLocation(FVector(PreviousX, PreviousY, GetActorLocation().Z));

	if (GetActorLocation().Z < this->FloorZ + this->FloorZOffset)
	{
		SetActorLocation(FVector(PreviousX, PreviousY, this->FloorZ + this->FloorZOffset));
	}
}

void AFloatingPawnBase::MiddleMousePressed()
{
	this->bMiddleMouseDown = true;
}

void AFloatingPawnBase::MiddleMouseReleased()
{
	this->bMiddleMouseDown = false;
}

void AFloatingPawnBase::MouseXAxis(float Value)
{
	if (!this->bMiddleMouseDown)
	{
		return;
	}

	if (this->bInvertMouseX)
	{
		Value = -Value;
	}

	FQuat DeltaRotation = FRotator(0.f, Value * MouseRotateSpeed * GetWorld()->GetDeltaSeconds(), 0.f).Quaternion();
	AddActorLocalRotation(DeltaRotation);
	SetActorRelativeRotation(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, 0.f));
}

void AFloatingPawnBase::MouseYAxis(float Value)
{
	if (!this->bMiddleMouseDown)
	{
		return;
	}

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