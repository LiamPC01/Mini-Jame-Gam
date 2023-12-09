// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "BulletActor.h"
#include "DrawDebugHelpers.h"
#include "FirstPersonCharacter.generated.h"


UCLASS()
class MINI_JAME_GAM_API AFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstPersonCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ABulletActor> ProjectileClass;

	// Casting own Capsule Component to primitive so it can be ignored by linetrace
	UCapsuleComponent* PlayerCapsule = GetCapsuleComponent();
	UPrimitiveComponent* PlayerCapsulePrim = Cast<UPrimitiveComponent>(PlayerCapsule);

	APlayerCameraManager* CamManager;
	FVector CamLocation;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	int Ammo;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	float FireRate;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	float bIsAutomatic;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	bool bIsShooting;

	FTimerHandle fireTimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	// Handles input for moving forward and backward.
	UFUNCTION()
	void MoveForward(float Value);

	// Handles input for moving right and left.
	UFUNCTION()
	void MoveRight(float Value);

	// Sets jump flag when key is pressed.
	UFUNCTION()
	void StartJump();

	// Clears jump flag when key is released.
	UFUNCTION()
	void StopJump();

	// Function that handles firing projectiles.
	UFUNCTION()
	void OnFire();

	// Function that handles firing projectiles.
	UFUNCTION()
	void StartFiring();

	// Function that handles firing projectiles.
	UFUNCTION()
	void StopFiring();

	// Hoover functions
	UFUNCTION()
	void Hoover();

	UFUNCTION()
	void StopHoover();

	//UFUNCTION()
	//void StopHoover();

	// FPS camera
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FPSMesh;

	// Gun muzzle offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sphere Overlap")
	class USphereComponent* DeadZoneSphere;
	
	



	

};
