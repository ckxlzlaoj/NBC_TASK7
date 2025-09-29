// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPlayerController.h"
#include "MyPawn.generated.h"

class UCapsuleComponent;
class USpringArmComponent; // ������ �� ���� Ŭ���� ���
class UCameraComponent;
class UInputMappingContext; // IMC ���� ���� ����
class UInputAction;
struct FInputActionValue;


UCLASS()
class MYPROJECT3_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SKMeshComp")
	USkeletalMeshComponent* Mesh;

	// ������ �� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpringArmComp")
	USpringArmComponent* SpringArm;
	// ī�޶� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* Camera;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	// IA_Move�� ������ ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	// IA_Jump�� ������ ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;
	// IA_Look�� ������ ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	// Movement Params
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 600.0f;      // ����/��

	UPROPERTY(EditAnywhere, Category = "Movement")
	float LookYawSpeed = 10.0f;     // ���콺 X �� Yaw(��/ƽ)

	UPROPERTY(EditAnywhere, Category = "Movement")
	float LookPitchSpeed = 10.0f;   // ���콺 Y �� Pitch(��/ƽ)

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MinPitch = -80.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxPitch = 80.0f;

	float CurrentPitch = 0.0f;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
