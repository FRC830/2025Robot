#include "HAL/CoralLauncherHAL.h"

void CoralLauncher::SetRightWheelSpeed(double speed)
{
    // todo
    m_RightWheelSpeed = speed;
    rightMotor.Set(m_RightWheelSpeed);
}
void CoralLauncher::SetLeftWheelSpeed(double speed)
{
    // todo
    m_LeftWheelSpeed = speed;
    leftMotor.Set(m_LeftWheelSpeed);
}
void CoralLauncher::SetIndexerSpeed(double speed)
{
    //todo idk what indexer is check CAD

}
double CoralLauncher::GetRightWheelSpeed()
{
    return m_RightWheelSpeed;
}
double CoralLauncher::GetLeftWheelSpeed()
{
    return m_LeftWheelSpeed;
}