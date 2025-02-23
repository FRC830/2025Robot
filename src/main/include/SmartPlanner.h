#pragma once

#include "MoveToPose.h"
#include "PhotonVisionCamera.h"

class SmartPlanner{
    public:
        SmartPlanner();
        ~SmartPlanner() = default;

        void RunPlanner();

    private:
        PhotonVisionCamera m_Cam;
        MoveToPose m_MoveToPose;
        int m_state;



};