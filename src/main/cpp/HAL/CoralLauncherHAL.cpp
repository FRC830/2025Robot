#include "HAL/CoralLauncherHAL.h"
/**/
CoralLauncher::CoralLauncher()
{

}
void CoralLauncher::SetWheelSpeeds(double rightSpeed, double leftSpeed)
{
    desiredRightSpeed = rightSpeed;
    desiredLeftSpeed = leftSpeed;
    rightMotor.Set(rightSpeed);
    leftMotor.Set(leftSpeed);
}
void CoralLauncher::SetIndexerSpeed(double indexerSpeed)
{
    m_IndexerSpeed = indexerSpeed;
    indexer.Set(indexerSpeed);
}
double CoralLauncher::GetRightWheelSpeed()
{
    m_RightWheelSpeed = rightMotor.GetEncoder().GetVelocity();
    return m_RightWheelSpeed;

}
double CoralLauncher::GetLeftWheelSpeed()
{
    m_LeftWheelSpeed = leftMotor.GetEncoder().GetVelocity();
    return m_LeftWheelSpeed;
}
bool CoralLauncher::AreFlywheelsAtDesiredSpeed()
{
    if((abs(m_RightWheelSpeed - desiredRightSpeed)<=num)&&(abs(m_LeftWheelSpeed - desiredLeftSpeed)<=num)){
        return true;
    }
    else{
        return false;
    }
}
bool CoralLauncher::BeamBreakStatus()
{
    //todo: implement beam break status code
    return m_beam_break.Get();
}