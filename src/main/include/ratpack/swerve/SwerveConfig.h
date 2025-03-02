#pragma once

#include <frc/AnalogEncoder.h>
#include <frc/geometry/Rotation2d.h>
#include <frc/geometry/Translation2d.h>
#include <ctre/phoenix6/CANcoder.hpp>
#include "rev/SparkMax.h"

// ###########################################################
// #                  Front Left Module                      #
// ###########################################################
// --------------------Absolute Encoder-----------------------
const int FL_ABS_ENC_PORT = 3;
const bool FL_ABS_ENC_INVERTED = false;
const frc::Rotation2d FL_ZERO_HEADING{units::degree_t{268.76f}};

ctre::phoenix6::hardware::CANcoder fl_abs_enc{FL_ABS_ENC_PORT};

// -----------------------Turn Motor--------------------------
const int FL_TURN_MTR_ID = 15;
const bool FL_TURN_MTR_INVERTED = true;

rev::spark::SparkMax fl_turn_mtr{FL_TURN_MTR_ID, rev::spark::SparkMax::MotorType::kBrushless};
rev::spark::SparkRelativeEncoder fl_turn_enc = fl_turn_mtr.GetEncoder();
rev::spark::SparkClosedLoopController fl_turn_pid = fl_turn_mtr.GetClosedLoopController();

// -----------------------Drive Motor-------------------------
const int FL_DRIVE_MTR_ID = 18;
const double FL_POSITION_CORRECTION_FACTOR = 1.0;

rev::spark::SparkMax fl_drive_mtr{FL_DRIVE_MTR_ID, rev::spark::SparkMax::MotorType::kBrushless};
rev::spark::SparkRelativeEncoder fl_drive_enc = fl_drive_mtr.GetEncoder();
rev::spark::SparkClosedLoopController fl_drive_pid = fl_drive_mtr.GetClosedLoopController();


// ###########################################################
// #                  Front Right Module                     #
// ###########################################################
// --------------------Absolute Encoder-----------------------
const int FR_ABS_ENC_PORT = 6;
const bool FR_ABS_ENC_INVERTED = false;
const frc::Rotation2d FR_ZERO_HEADING{units::degree_t{270.61f}};

ctre::phoenix6::hardware::CANcoder fr_abs_enc{FR_ABS_ENC_PORT};

// -----------------------Turn Motor--------------------------
const int FR_TURN_MTR_ID = 17;
const bool FR_TURN_MTR_INVERTED = true;

rev::spark::SparkMax fr_turn_mtr{FR_TURN_MTR_ID, rev::spark::SparkMax::MotorType::kBrushless};
rev::spark::SparkRelativeEncoder fr_turn_enc = fr_turn_mtr.GetEncoder();
rev::spark::SparkClosedLoopController fr_turn_pid = fr_turn_mtr.GetClosedLoopController();

// -----------------------Drive Motor-------------------------
const int FR_DRIVE_MTR_ID = 19;
const double FR_POSITION_CORRECTION_FACTOR = 1.0;

rev::spark::SparkMax fr_drive_mtr{FR_DRIVE_MTR_ID, rev::spark::SparkMax::MotorType::kBrushless};
rev::spark::SparkRelativeEncoder fr_drive_enc = fr_drive_mtr.GetEncoder();
rev::spark::SparkClosedLoopController fr_drive_pid = fr_drive_mtr.GetClosedLoopController(); 


// ###########################################################
// #                  Back Left Module                       #
// ###########################################################
// --------------------Absolute Encoder-----------------------
const int BL_ABS_ENC_PORT = 12;
const bool BL_ABS_ENC_INVERTED = false;
const frc::Rotation2d BL_ZERO_HEADING{units::degree_t{3.86f}};

ctre::phoenix6::hardware::CANcoder bl_abs_enc{BL_ABS_ENC_PORT};


// -----------------------Turn Motor--------------------------
const int BL_TURN_MTR_ID = 7;
const bool BL_TURN_MTR_INVERTED = true;

rev::spark::SparkMax bl_turn_mtr{BL_TURN_MTR_ID, rev::spark::SparkMax::MotorType::kBrushless};
rev::spark::SparkRelativeEncoder bl_turn_enc = bl_turn_mtr.GetEncoder();
rev::spark::SparkClosedLoopController bl_turn_pid = bl_turn_mtr.GetClosedLoopController();

// -----------------------Drive Motor-------------------------
const int BL_DRIVE_MTR_ID = 8;
const double BL_POSITION_CORRECTION_FACTOR = 1.0;

rev::spark::SparkMax bl_drive_mtr{BL_DRIVE_MTR_ID, rev::spark::SparkMax::MotorType::kBrushless};
rev::spark::SparkRelativeEncoder bl_drive_enc = bl_drive_mtr.GetEncoder();
rev::spark::SparkClosedLoopController bl_drive_pid = bl_drive_mtr.GetClosedLoopController();


// ###########################################################
// #                  Back Right Module                      #
// ###########################################################
// --------------------Absolute Encoder-----------------------
const int BR_ABS_ENC_PORT = 9;
const bool BR_ABS_ENC_INVERTED = false;
const frc::Rotation2d BR_ZERO_HEADING{units::degree_t{176.48f}};

ctre::phoenix6::hardware::CANcoder br_abs_enc{BR_ABS_ENC_PORT};

// -----------------------Turn Motor--------------------------
const int BR_TURN_MTR_ID = 2;
const bool BR_TURN_MTR_INVERTED = true;

rev::spark::SparkMax br_turn_mtr{BR_TURN_MTR_ID, rev::spark::SparkMax::MotorType::kBrushless};
rev::spark::SparkRelativeEncoder br_turn_enc = br_turn_mtr.GetEncoder();
rev::spark::SparkClosedLoopController br_turn_pid = br_turn_mtr.GetClosedLoopController();

// -----------------------Drive Motor-------------------------
const int BR_DRIVE_MTR_ID = 20;
const double BR_POSITION_CORRECTION_FACTOR = 1.0;

rev::spark::SparkMax br_drive_mtr{BR_DRIVE_MTR_ID, rev::spark::SparkMax::MotorType::kBrushless};
rev::spark::SparkRelativeEncoder br_drive_enc = br_drive_mtr.GetEncoder();
rev::spark::SparkClosedLoopController br_drive_pid = br_drive_mtr.GetClosedLoopController(); 


// ###########################################################
// #                     Swerve Drive                        #
// ###########################################################
const double ROBOT_WIDTH_M = 0.617;
const double ROBOT_LENGTH_M = 0.617;

const frc::Translation2d fl_position(units::meter_t{ROBOT_LENGTH_M / 2.0}, units::meter_t{ROBOT_WIDTH_M / 2.0});
const frc::Translation2d fr_position(units::meter_t{ROBOT_LENGTH_M / 2.0}, units::meter_t{-ROBOT_WIDTH_M / 2.0});
const frc::Translation2d bl_position(units::meter_t{-ROBOT_LENGTH_M / 2.0}, units::meter_t{ROBOT_WIDTH_M / 2.0});
const frc::Translation2d br_position(units::meter_t{-ROBOT_LENGTH_M / 2.0}, units::meter_t{-ROBOT_WIDTH_M / 2.0});

// ------------------------Turn Motor-------------------------
const double TURN_GEAR_RATIO = 10.2857;
const double MOTOR_ROT_TO_DEG = 360.0 / TURN_GEAR_RATIO;

const double TURN_P = 0.045;
const double TURN_I = 0.0;
const double TURN_D = 0.003;
const double TURN_FF = 0.0;

// ------------------------Drive Motor------------------------
const double DRIVE_GEAR_RATIO = 5.5;
const double WHEEL_DIAMETER_FT = 0.333; // 4 inches
const double MOTOR_ROT_TO_FT = (WHEEL_DIAMETER_FT * 3.14159) / DRIVE_GEAR_RATIO;

const double DRIVE_P = 0.08;
const double DRIVE_I = 0.0;
const double DRIVE_D = 0.1;
const double DRIVE_FF = 0.0;

// --------------------------Gyro-----------------------------
const bool GYRO_INVERTED = true;
const frc::Rotation2d GYRO_ZERO_HEADING{units::degree_t{0.0f}};

// --------------------------Swerve---------------------------
const double MAX_DRIVE_SPEED_FPS = 18.0;
const double MAX_ANGULAR_VELOCITY_DEGPS = 540.0;
const double CONTROLLER_DEADZONE = 0.1;
const int TURN_MOTOR_CURRENT_LIMIT = 20;
const int DRIVE_MOTOR_CURRENT_LIMIT = 30;
const double SWERVE_VOLTAGE_COMPENSATION = 10.5;
const bool IS_DRIVE_IN_COAST = false;
const bool IS_ROBOT_ORIENTED_DRIVE = false;
