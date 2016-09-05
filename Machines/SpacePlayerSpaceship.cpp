// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#include "SpaceBattles.h"
#include "SpacePlayerSpaceship.h"

#include "SpaceshipParts/SpaceMachineGunComponent.h"
#include "SpaceshipParts/SpaceRocketGunComponent.h"
#include "SpaceSpaceshipMovementComponent.h"

#include "Projectiles/SpaceProjectile.h"

#include "SpaceDynamicBarrier.h"

ASpacePlayerSpaceship::ASpacePlayerSpaceship()
{
	PrimaryActorTick.bCanEverTick = false;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	MeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	MeshComponent->SetCollisionResponseToChannel(ECC_Pickup, ECollisionResponse::ECR_Overlap);
	MeshComponent->SetCollisionResponseToChannel(ECC_Boundary, ECollisionResponse::ECR_Overlap);
	MeshComponent->bGenerateOverlapEvents = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("ArmSpring");
	SpringArmComponent->AttachTo(RootComponent);
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->TargetArmLength = 25.f;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 5.f;
	SpringArmComponent->bEnableCameraRotationLag = true;
	SpringArmComponent->CameraRotationLagSpeed = 5.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->AttachTo(SpringArmComponent);

	RocketGunComponent = CreateDefaultSubobject<USpaceRocketGunComponent>("RocketGun");
}

void ASpacePlayerSpaceship::SetupPlayerInputComponent(UInputComponent * InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("MachineGun", EInputEvent::IE_Pressed, MachineGunComponent, &USpaceMachineGunComponent::StartShooting);
	InputComponent->BindAction("MachineGun", EInputEvent::IE_Released, MachineGunComponent, &USpaceMachineGunComponent::StopShooting);
	InputComponent->BindAction("RocketGun", EInputEvent::IE_Pressed, RocketGunComponent, &USpaceRocketGunComponent::Shoot);

	InputComponent->BindAction("BoostedMove", EInputEvent::IE_Pressed, MovementComponent, &USpaceSpaceshipMovementComponent::Accelerate);
	InputComponent->BindAction("BoostedMove", EInputEvent::IE_Released, MovementComponent, &USpaceSpaceshipMovementComponent::Decelerate);

	InputComponent->BindAction("Exit", EInputEvent::IE_Pressed, this, &ASpacePlayerSpaceship::ExitGameRequest);

	InputComponent->BindAxis("SteerUp", MovementComponent, &USpaceSpaceshipMovementComponent::SteerUp);
	InputComponent->BindAxis("SteerRight", MovementComponent, &USpaceSpaceshipMovementComponent::SteerRight);
}

void ASpacePlayerSpaceship::IgnoreProjectile(ASpaceProjectile *Projectile)
{
	Super::IgnoreProjectile(Projectile);

	if (Barrier)
	{
		Barrier->IgnoreActorWhenMoving(Projectile);
		Projectile->IgnoreActorWhenMoving(Barrier);
	}
}

void ASpacePlayerSpaceship::AddBarrier(float BarrierLifeSpan)
{
	if (!Barrier)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		Barrier = GetWorld()->SpawnActor<ASpaceDynamicBarrier>(BarrierTemplate, GetActorLocation(), GetActorRotation(), SpawnParameters);

		MeshComponent->IgnoreActorWhenMoving(Barrier, true);
	}

	Barrier->SetLifeSpan(Barrier->GetLifeSpan() + BarrierLifeSpan);
}

void ASpacePlayerSpaceship::OnDeath()
{
	Super::OnDeath();

	if (Barrier)
	{
		Barrier->Destroy();
	}
}

void ASpacePlayerSpaceship::ExitGameRequest()
{
	static_cast<APlayerController*>(GetController())->ConsoleCommand("quit");
}


