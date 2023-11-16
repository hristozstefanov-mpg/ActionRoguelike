#include "RGCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "RGInteractionComponent.h"

ARGCharacter::ARGCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	InteractionComponent = CreateDefaultSubobject<URGInteractionComponent>(TEXT("InteractionComponent"));

	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	CharacterMovementComponent->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

void ARGCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add the default input mapping context, this includes basic actions such as move, jump and look
	if (auto* PlayerController = GetController<APlayerController>())
	{
		if (auto* EnhancedInput = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			EnhancedInput->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ARGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind input actions to functions
	if (auto* EnhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARGCharacter::HandleInput_Move);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ARGCharacter::HandleInput_Jump);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARGCharacter::HandleInput_Look);
		EnhancedInput->BindAction(PrimaryAttackAction, ETriggerEvent::Triggered, this, &ARGCharacter::HandleInput_PrimaryAttack);
		EnhancedInput->BindAction(SecondaryAttackAction, ETriggerEvent::Triggered, this, &ARGCharacter::HandleInput_SecondaryAttack);
		EnhancedInput->BindAction(TrietaryAttackAction, ETriggerEvent::Triggered, this, &ARGCharacter::HandleInput_TrietaryAttack);
		EnhancedInput->BindAction(PrimaryInteractAction, ETriggerEvent::Triggered, this, &ARGCharacter::HandleInput_PrimaryInteract);
	}
}

void ARGCharacter::HandleInput_Move(const FInputActionValue& Value)
{
	auto Movement2D = Value.Get<FInputActionValue::Axis2D>();

	// For the purposes of movement we're only interested in the Yaw component of the rotation
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;

	// Get Forward and Right vectors relative to the control rotation
	FVector ForwardVector = ControlRotation.Vector();
	FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);

	// Add the movement vector to the character
	AddMovementInput(ForwardVector, Movement2D.Y);
	AddMovementInput(RightVector, Movement2D.X);
}

void ARGCharacter::HandleInput_Jump(const FInputActionValue& Value)
{
	Jump();
}

void ARGCharacter::HandleInput_Look(const FInputActionValue& Value)
{
	auto Look2D = Value.Get<FInputActionValue::Axis2D>();

	// Horizontal look controls the yaw, vertical look - the pitch
	AddControllerYawInput(Look2D.X);
	AddControllerPitchInput(Look2D.Y);
}

void ARGCharacter::HandleInput_PrimaryAttack(const FInputActionValue& Value)
{
	PlayAnimMontage(AttackAnimation);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ARGCharacter::TimeElapsed_PrimaryAttack, 0.2f);
}

void ARGCharacter::TimeElapsed_PrimaryAttack()
{
	SpawnProjectile(PrimaryProjectileClass);
}

void ARGCharacter::HandleInput_SecondaryAttack(const FInputActionValue& Value)
{
	PlayAnimMontage(AttackAnimation);

	GetWorldTimerManager().SetTimer(TimerHandle_SecondaryAttack, this, &ARGCharacter::TimeElapsed_SecondaryAttack, 0.2f);
}

void ARGCharacter::TimeElapsed_SecondaryAttack()
{
	SpawnProjectile(SecondaryProjectileClass);
}

void ARGCharacter::HandleInput_TrietaryAttack(const FInputActionValue& Value)
{
	PlayAnimMontage(AttackAnimation);

	GetWorldTimerManager().SetTimer(TimerHandle_TrietaryAttack, this, &ARGCharacter::TimeElapsed_TrietaryAttack, 0.2f);
}

void ARGCharacter::TimeElapsed_TrietaryAttack()
{
	SpawnProjectile(TrietaryProjectileClass);
}

void ARGCharacter::SpawnProjectile(TSubclassOf<AActor> ProjectileClass)
{
	FVector SpawnLocation;
	if (ensureMsgf(ProjectileSpawnSocket.IsValid(), TEXT("Please assign ProjectileSpawnSocket for primary attack projectiles")))
	{
		SpawnLocation = GetMesh()->GetSocketLocation(ProjectileSpawnSocket);
	}
	else
	{
		SpawnLocation = GetActorLocation();
	}

	FRotator SpawnRotation = GetControlRotation();

	FVector TraceStartLocation = CameraComponent->GetComponentLocation();
	FVector TraceEndLocation = TraceStartLocation + CameraComponent->GetComponentTransform().GetRotation().Vector() * 10000.0f;

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStartLocation, TraceEndLocation, ECollisionChannel::ECC_Visibility))
	{
		FVector DirectionVector = HitResult.ImpactPoint - SpawnLocation;
		SpawnRotation = FRotationMatrix::MakeFromX(DirectionVector).Rotator();
	}

	FTransform SpawnTransform = FTransform(SpawnRotation, SpawnLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParams);
}

void ARGCharacter::HandleInput_PrimaryInteract(const struct FInputActionValue& Value)
{
	InteractionComponent->PrimaryInteract();
}

void ARGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
