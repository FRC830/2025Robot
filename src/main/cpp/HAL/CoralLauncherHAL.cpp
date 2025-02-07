#include "HAL/CoralLauncherHAL.h"
/**/
CoralLauncher::CoralLauncher()
{

}
void CoralLauncher::SetWheelSpeeds(double rightSpeed, double leftSpeed)
{
    // todo
    m_RightWheelSpeed = rightSpeed;
    rightMotor.Set(m_RightWheelSpeed);
    // todo
    m_LeftWheelSpeed = leftSpeed;
    leftMotor.Set(m_LeftWheelSpeed);
}
void CoralLauncher::SetIndexerSpeed(double indexerSpeed)
{
    //todo idk what indexer is check CAD | indexer is the thing that moves the coral into the shooter btw
    m_IndexerSpeed = indexerSpeed;
    indexer.Set(indexerSpeed);
}
double CoralLauncher::GetRightWheelSpeed()
{
    return m_RightWheelSpeed;
}
double CoralLauncher::GetLeftWheelSpeed()
{
    return m_LeftWheelSpeed;
}