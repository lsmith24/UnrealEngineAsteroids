// Fill out your copyright notice in the Description page of Project Settings.
#include "Asteroid.h"
#include "UObject/ConstructorHelpers.h" 
#include "Kismet/GameplayStatics.h" 

// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Our root component will be a box that reacts to physics 
	AsteroidBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = AsteroidBoxComponent;
	AsteroidBoxComponent->InitBoxExtent(FVector(12.0f, 15.0f, 12.0f));
	AsteroidBoxComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	AsteroidBoxComponent->SetSimulatePhysics(true);
	AsteroidBoxComponent->SetEnableGravity(false);
	AsteroidBoxComponent->SetNotifyRigidBodyCollision(true);

	static ConstructorHelpers::FObjectFinder<UBlueprint>
		FindExplosion(TEXT("Blueprint'/Game/ExplosionBP.ExplosionBP'"));
	if (FindExplosion.Object) {
		Explosion = (UClass*)FindExplosion.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue>
		explosionSound(TEXT("SoundCue'/Game/ExplosionSound.ExplosionSound'"));
	if (explosionSound.Object != NULL)
	{
		explosionSoundCue = (USoundCue*)explosionSound.Object;
	}
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &AAsteroid::onHit);
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAsteroid::onHit(AActor* SelfActor, class AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && (OtherActor != this) && OtherActor->IsA(ABullet::StaticClass()))
	{
		Destroy();
		OtherActor->Destroy();
		UWorld* const World = GetWorld();
		if (World) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
			World->SpawnActor<AActor>(Explosion, GetActorLocation(),
				GetActorRotation(), SpawnParams);

			UGameplayStatics::PlaySoundAtLocation(World, explosionSoundCue,
				GetActorLocation());

			HitDelegate.Execute();
		}
	}
}