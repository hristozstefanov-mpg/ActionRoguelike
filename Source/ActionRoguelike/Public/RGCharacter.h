#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RGCharacter.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARGCharacter();

protected:

	/** Third person camera attached to this character. */
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;

	/** Spring arm used for attaching the camera. */
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComponent;

	/** Interaction handling behavior. */
	UPROPERTY(VisibleAnywhere)
	class URGInteractionComponent* InteractionComponent;

	/** Input mapping context to use for all default actions. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* DefaultMappingContext;

	/** Reference to the move action, should be the same as the input action defined in the DefaultMappingContext. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* MoveAction;

	/** Reference to the jump action, should be the same as the input action defined in the DefaultMappingContext. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* JumpAction;

	/** Reference to the look action, should be the same as the input action defined in the DefaultMappingContext. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* LookAction;

	/** Reference to the primary attack action, should be the same as the input action defined in the DefaultMappingContext. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* PrimaryAttackAction;

	/** Reference to the primary interaction action, should be the same as the input action defined in the DefaultMappingContext. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* PrimaryInteractAction;

	/** Projectile class to spawn when using primary attack. */
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	/** The character mesh socket to use as spawn point for projectiles. */
	UPROPERTY(EditAnywhere)
	FName ProjectileSpawnSocket;

public:
	/** Initializes the character */
	virtual void BeginPlay() override;

	/** Updates the character every frame */
	virtual void Tick(float DeltaTime) override;

protected:

	/** Sets up input bindings mapping actions to specific functions */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Handles character movement action */
	virtual void HandleInput_Move(const struct FInputActionValue& Value);

	/** Handles character jump action */
	virtual void HandleInput_Jump(const FInputActionValue& Value);

	/** Handles character camera look action */
	virtual void HandleInput_Look(const struct FInputActionValue& Value);

	/** Handles character main attack action */
	virtual void HandleInput_PrimaryAttack(const struct FInputActionValue& Value);

	/** Handles character main interact action */
	virtual void HandleInput_PrimaryInteract(const struct FInputActionValue& Value);
};
