#pragma once

#include <frc2/command/CommandHelper.h>
#include "RobotControlData.h"

class UseSmartPlan : public frc2::CommandHelper<frc2::Command, UseSmartPlan>
{
public:
    explicit UseSmartPlan(RobotControlData& data);
    ~UseSmartPlan() = default;

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;

private:
    RobotControlData& m_data;
};