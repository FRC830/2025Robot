#pragma once

#include <frc2/command/CommandHelper.h>
#include "RobotControlData.h"

class RaiseArmToBottom : public frc2::CommandHelper<frc2::Command, RaiseArmToBottom>
{
public:
    RaiseArmToBottom(RobotControlData& data);
    ~RaiseArmToBottom() = default;

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;

private:
    RobotControlData& m_data;
};