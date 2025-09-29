// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "MyPlayerController.h"
#include "InputActionValue.h"
// Sets default values
AMyPawn::AMyPawn()
{

    
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    // Root capsule
    Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
    Capsule->InitCapsuleSize(34.f, 88.f);
    Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Capsule->SetCollisionObjectType(ECC_Pawn);
    Capsule->SetCollisionResponseToAllChannels(ECR_Block);
    Capsule->SetSimulatePhysics(false);
    RootComponent = Capsule;

    // Mesh
    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);
    Mesh->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
    Mesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
    Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
    Mesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
    Mesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
    Mesh->SetSimulatePhysics(false);

    // SpringArm
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 350.f;
    SpringArm->bUsePawnControlRotation = true;
    SpringArm->bEnableCameraLag = true;
    SpringArm->CameraLagSpeed = 10.f;
    SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 60.f));

    // Camera
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;

    bUseControllerRotationYaw = true;
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
    if (GetWorld())
    {
        if (UGameInstance* GameInstance = GetWorld()->GetGameInstance())
        {
            if (GameInstance->GetLocalPlayers().Num() > 0)
            {
                if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GameInstance->GetLocalPlayers()[0]->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
                {
                    if (InputMappingContext)
                    {
                        Subsystem->AddMappingContext(InputMappingContext, 0);
                    }
                }
            }
        }
    }
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

  /*  if (UEnhancedInputComponent* EnhancedInput
        = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()))
        {
            if (PlayerController->MoveAction)
            {

                UE_LOG(LogTemp, Warning, TEXT("MoveAction ���ε� ����!"));
                EnhancedInput->BindAction(PlayerController->MoveAction
                    , ETriggerEvent::Triggered
                    , this
                    , &AMyPawn::Move);
            }

            if (PlayerController->LookAction)
            {
                EnhancedInput->BindAction(PlayerController->LookAction
                    , ETriggerEvent::Triggered
                    , this
                    , &AMyPawn::Look);

            }
        }
    }*/


    UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent called!"));

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (MoveAction)
        {
            EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPawn::Move);
            UE_LOG(LogTemp, Warning, TEXT("MoveAction binding added!"));
        }
    }

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (LookAction)
        {
            EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPawn::Look);
            UE_LOG(LogTemp, Warning, TEXT("LookAction binding added!"));
        }
    }
}

void AMyPawn::Look(const FInputActionValue& value)
{
    FVector2D LookInput = value.Get<FVector2D>();

    // X�� �¿� ȸ�� (Yaw), Y�� ���� ȸ�� (Pitch)
    // �¿� ȸ��
    AddControllerYawInput(LookInput.X);
    // ���� ȸ��
    AddControllerPitchInput(LookInput.Y);
}

void AMyPawn::Move(const FInputActionValue& value)
{
    // 2DVector�� �ޱ�� �ߴ�.
    if (!Controller) return;

    const FVector2d MoveInput = value.Get<FVector2d>();

    const float Dt = GetWorld() ? GetWorld()->GetDeltaSeconds() : 0.016f;

    // ����/�¿� = ���� ��� �̵�
    const FVector Forward = GetActorForwardVector();
    const FVector Right = GetActorRightVector();
    FVector Delta = (Forward * MoveInput.Y + Right * MoveInput.X); // �װ� X=����, Y=�¿�� ���� �� ����
    Delta.Z = 0.f;

    AddActorWorldOffset(Delta * MoveSpeed * Dt, false); // Sweep=true

    UE_LOG(LogTemp, Warning, TEXT("Forward: %s"), *Forward.ToString());
}