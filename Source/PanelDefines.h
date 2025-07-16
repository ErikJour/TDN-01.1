/*
  ==============================================================================

    PanelDefines.h
    Created: 16 Jul 2025 10:21:13am
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once

#define PANEL_BASE_WIDTH 1000
#define PANEL_BASE_HEIGHT 660

#define PANEL_CENTER_WIDTH 700
#define PANEL_CENTER_HEIGHT 530

#define PANEL_LEFT_WIDTH 100
#define PANEL_LEFT_HEIGHT PANEL_BASE_HEIGHT

#define PANEL_RIGHT_WIDTH (PANEL_BASE_WIDTH - PANEL_CENTER_WIDTH - PANEL_LEFT_WIDTH)
#define PANEL_RIGHT_HEIGHT PANEL_BASE_HEIGHT

#define PANEL_TOP_WIDTH PANEL_BASE_WIDTH
#define PANEL_TOP_HEIGHT 30

#define PANEL_BOTTOM_WIDTH PANEL_BASE_WIDTH
#define PANEL_BOTTOM_HEIGHT (PANEL_BASE_HEIGHT - PANEL_CENTER_HEIGHT - PANEL_TOP_HEIGHT)
