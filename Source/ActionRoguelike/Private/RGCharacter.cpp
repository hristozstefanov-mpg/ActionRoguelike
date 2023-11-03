#include "RGCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"

ARGCharacter::ARGCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
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
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARGCharacter::HandleInput_Look);
	}
}

void ARGCharacter::HandleInput_Move(const FInputActionValue& Value)
{
	auto InputAxis2D = Value.Get<FInputActionValue::Axis2D>();

	// Convert from input coordinate space (X right, Y up) to character relative coordinates (X forward, Y right)
	auto RelativeInput3D = FVector(InputAxis2D.Y, InputAxis2D.X, 0.0f);

	// Convert from character relative coordinates to world space coordinates (based on character orientation)
	FQuat ActorRotation = GetActorQuat();
	FVector WorldSpaceInput3D = ActorRotation * RelativeInput3D;

	// Add the movement vector to the character
	AddMovementInput(WorldSpaceInput3D);
}

void ARGCharacter::HandleInput_Look(const FInputActionValue& Value)
{
	auto Look2D = Value.Get<FInputActionValue::Axis2D>();

	// Horizontal look rotates the character
	AddControllerYawInput(Look2D.X);

	// Vertical look rotates only the camera (along the spring arm attached to the character)
	FRotator CameraPitch = FRotator::ZeroRotator;
	CameraPitch.Pitch = Look2D.Y;
	SpringArmComponent->AddLocalRotation(CameraPitch);
}

void ARGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
