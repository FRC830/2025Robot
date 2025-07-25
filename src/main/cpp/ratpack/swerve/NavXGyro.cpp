#include "ratpack/swerve/NavXGyro.h"


void NavXGyro::Configure(GyroConfig &config)
{
    m_gyro = new studica::AHRS(studica::AHRS::NavXComType::kMXP_SPI);
    m_is_inverted = config.is_inverted;
    m_zero_heading = config.zero_heading;
}

frc::Rotation3d NavXGyro::GetYawPitchRoll() 
{
    units::radian_t yaw = units::radian_t(m_gyro->GetYaw());
    units::radian_t pitch = units::radian_t(m_gyro->GetPitch());
    units::radian_t roll = units::radian_t(m_gyro->GetRoll());
    frc::Rotation3d yaw_pitch_roll = frc::Rotation3d(roll, pitch, yaw);
    return yaw_pitch_roll;
}

frc::Rotation2d NavXGyro::GetHeading()
{
    frc::Rotation2d rawHeading = GetRawHeading();
    double heading = double((rawHeading - m_zero_heading).Degrees());

    if (heading < 0) 
    {
        heading += 360.0f;
    }

    return frc::Rotation2d(units::degree_t(heading));
}

frc::Rotation2d NavXGyro::GetRawHeading() 
{
    double rawHeading = std::fmod(m_gyro->GetAngle(), 360.0);

    if (m_is_inverted) 
    {
        rawHeading = std::abs(360.0f - rawHeading);
    }

    return frc::Rotation2d(units::degree_t(rawHeading));
}

bool NavXGyro::GetInverted() 
{
    return m_is_inverted;
}

void NavXGyro::SetInverted(bool inverted) 
{
    m_is_inverted = inverted;
}

void NavXGyro::SetZeroHeading(double zero_heading) 
{
    m_zero_heading = frc::Rotation2d(units::degree_t(zero_heading));
}

void NavXGyro::Reset()
{
    m_gyro->Reset();
}
