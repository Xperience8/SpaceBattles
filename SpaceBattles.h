// Copyright 2015 Patrick Jurasek. All Rights Reserved.

#pragma once

#include "Engine.h"

#define ECC_Boundary ECollisionChannel::ECC_GameTraceChannel1
#define ECC_Pickup ECollisionChannel::ECC_GameTraceChannel2
#define ECC_Spaceship ECollisionChannel::ECC_GameTraceChannel3
#define ECC_Barrier ECollisionChannel::ECC_GameTraceChannel4
#define ECC_Projectile ECollisionChannel::ECC_GameTraceChannel5

const float INSTANT_KILL_DAMAGE = 0.f;