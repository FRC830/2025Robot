#pragma once

#include <frc2/command/CommandHelper.h>
#include "RobotControlData.h"

class LowerArm : public frc2::CommandHelper<frc2::Command, LowerArm>
{
public:
    explicit LowerArm(RobotControlData& data);
    ~LowerArm() = default;

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;

private:
    RobotControlData& m_data;
};