// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonCharacter.h"

// Sets default values
AFirstPersonCharacter::AFirstPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a first person camera component.
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	// Attach the camera component to our capsule component.
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// Position the camera slightly above the eyes.
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	// Enable the pawn to control camera rotation.
	FPSCameraComponent->bUsePawnControlRotation = true;
	
	// Create a first person mesh component for the owning player.
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	// Only the owning player sees this mesh.
	FPSMesh->SetOnlyOwnerSee(true);

	// Attach the FPS mesh to the FPS camera.
	FPSMesh->SetupAttachment(FPSCameraComponent);

	// Disable some environmental shadows to preserve the illusion of having a single mesh.
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// The owning player doesn't see the regular (third-person) body mesh.
	GetMesh()->SetOwnerNoSee(true);


	DeadZoneSphere = CreateDefaultSubobject<USphereComponent>(FName("Dead Zone Sphere"));
	DeadZoneSphere->SetSphereRadius(32);
	DeadZoneSphere->SetWorldLocation(FVector(92.37735f,24.219597f, 113.603401f));
	DeadZoneSphere->SetWorldRotation(FRotator(-10.903551f,-22.635757f, 26.588614f));
	DeadZoneSphere->SetWorldScale3D(FVector(1.1425f,3.794096, 3.794096f));
	DeadZoneSphere->SetupAttachment(FPSCameraComponent);
	
	Ammo = 100;
	FireRate = 0.05f;
	bIsAutomatic = true;
	bIsShooting = false;

}

// Called when the game starts or when spawned
void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		// Display a debug message for five seconds. 
		// The -1 "Key" value argument prevents the message from being updated or refreshed.
		
	}

	FTimerHandle TimerHandle;
	//GetWorldTimerManager().SetTimer(TimerHandle, this, &AFirstPersonCharacter::CountDown);
}

// Called every frame
void AFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &AFirstPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFirstPersonCharacter::MoveRight);

	// Set up "look" bindings.
	PlayerInputComponent->BindAxis("Turn", this, &AFirstPersonCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFirstPersonCharacter::AddControllerPitchInput);

	// Set up "action" bindings.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFirstPersonCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFirstPersonCharacter::StopJump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFirstPersonCharacter::StartFiring);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFirstPersonCharacter::StopFiring);

	
	//PlayerInputComponent->BindAction("SpeedChange", IE_Pressed, this, &AFirstPersonCharacter::SpeedUp);
	//PlayerInputComponent->BindAction("SpeedChange", IE_Pressed, this, &AFirstPersonCharacter::SpeedDown);
	

}

void AFirstPersonCharacter::MoveForward(float Value)
{
	// Find out which way is "forward" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AFirstPersonCharacter::MoveRight(float Value)
{
	// Find out which way is "right" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AFirstPersonCharacter::StartJump()
{
	bPressedJump = true;
}

void AFirstPersonCharacter::StopJump()
{
	bPressedJump = false;
}

void AFirstPersonCharacter::OnFire()
{
	if(bIsShooting)
	{

		if(ProjectileClass != NULL)
		{
			if(Ammo > 0)
			{
				CamManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
				CamLocation = CamManager->GetCameraLocation();

				FVector SpawnLocation = (CamManager->GetActorForwardVector() * 200) + CamLocation;
				FRotator SpawnRotation = CamManager->GetCameraRotation();
				GetWorld()->SpawnActor<ABulletActor>(ProjectileClass, SpawnLocation, SpawnRotation);

				GetWorld()->GetTimerManager().SetTimer(fireTimerHandle, this, &AFirstPersonCharacter::OnFire, FireRate, false);
				Ammo-= 1;
				UGameplayStatics::PlaySound2D(GetWorld(), Shoot, 1, 1, 0);
			}
			

		}else
		{
			
		}
	}
}



void AFirstPersonCharacter::StopFiring()
{
	bIsShooting = false;
	fireTimerHandle.Invalidate();
}

void AFirstPersonCharacter::CountDown()
{
	
}

void AFirstPersonCharacter::StartFiring()
{
	bIsShooting = true;
	OnFire();
}
