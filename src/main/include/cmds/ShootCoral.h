#pragma once

#include <frc2/command/CommandHelper.h>
#include "RobotControlData.h"
#include <frc/Timer.h>

class ShootCoral : public frc2::CommandHelper<frc2::Command, ShootCoral>
{
public:
    explicit ShootCoral(RobotControlData& data);
    ~ShootCoral() = default;

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;

private:
    RobotControlData& m_data;
    frc::Timer m_timer;
    int m_state;
};