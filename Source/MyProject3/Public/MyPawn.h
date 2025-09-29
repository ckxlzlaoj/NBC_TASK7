// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPlayerController.h"
#include "MyPawn.generated.h"

class UCapsuleComponent;
class USpringArmComponent; // 스프링 암 관련 클래스 헤더
class UCameraComponent;
class UInputMappingContext; // IMC 관련 전방 선언
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

	// 스프링 암 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpringArmComp")
	USpringArmComponent* SpringArm;
	// 카메라 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* Camera;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	// IA_Move를 지정할 변수

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	// IA_Jump를 지정할 변수

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;
	// IA_Look를 지정할 변수

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	// Movement Params
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 600.0f;      // 유닛/초

	UPROPERTY(EditAnywhere, Category = "Movement")
	float LookYawSpeed = 10.0f;     // 마우스 X → Yaw(도/틱)

	UPROPERTY(EditAnywhere, Category = "Movement")
	float LookPitchSpeed = 10.0f;   // 마우스 Y → Pitch(도/틱)

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
