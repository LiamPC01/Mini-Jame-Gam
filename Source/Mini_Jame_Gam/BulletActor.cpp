// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create components
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(BoxComp);

	//attach components
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->SetSimulatePhysics(true);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	StaticMeshComp->AttachToComponent(BoxComp, FAttachmentTransformRules::KeepRelativeTransform);

	//Setting the Sphere radius to be of a smaller size in line with the Static Mesh.
	FVector BoxExtent(50, 50, 50);
	BoxComp->SetBoxExtent(BoxExtent);

	//Setting the Static Mesh Scale and Location to fit the radius of the Sphere.
	StaticMeshComp->SetRelativeLocation(FVector(0.0, 0.0, -40));
	StaticMeshComp->SetRelativeScale3D(FVector(0.75, 0.75, 0.75));

	//Using Constructor Helpers to set our Static Mesh Comp with a Sphere Shape.
	static ConstructorHelpers::FObjectFinder<UStaticMesh>BoxMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	StaticMeshComp->SetStaticMesh(BoxMeshAsset.Object);

	USceneComponent* Component = GetRootComponent();
	SetRootComponent(Component);

	if (!ProjectileMovementComponent)
	{

		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 1000.0f;
		ProjectileMovementComponent->MaxSpeed = 1000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
		

	}

}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

