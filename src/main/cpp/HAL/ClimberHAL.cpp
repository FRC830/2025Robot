#include "HAL/ClimberHAL.h"
#include <rev/config/SparkMaxConfig.h>
#include "ratpack/SparkMaxDebugMacro.h"
#include "MechanismConfig.h"

Climber::Climber()
{
    
}

void Climber::SetClimberSpeed(double speed)
{
    m_climberMotor.Set(speed);
}

double Climber::GetClimberSpeed()
{
    return m_climberMotor.GetEncoder().GetVelocity();
}
