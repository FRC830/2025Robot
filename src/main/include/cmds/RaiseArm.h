#pragma once

#include <frc2/command/CommandHelper.h>
#include "RobotControlData.h"

class RaiseArm : public frc2::CommandHelper<frc2::Command, RaiseArm>
{
public:
    explicit RaiseArm(RobotControlData& data);
    ~RaiseArm() = default;

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;

private:
    RobotControlData& m_data;
};