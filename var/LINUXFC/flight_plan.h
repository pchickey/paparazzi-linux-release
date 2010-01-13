/* This file has been generated from /home/pat/paparazzi3/conf/flight_plans/basic.xml */
/* Please DO NOT EDIT */

#ifndef FLIGHT_PLAN_H
#define FLIGHT_PLAN_H 

#include "std.h"
#ifdef USE_MODULES
#include "modules.h"
#endif
#include "nav_line.h"
#include "datalink.h"
#define FLIGHT_PLAN_NAME "Basic"
#define NAV_UTM_EAST0 360285
#define NAV_UTM_NORTH0 4813595
#define NAV_UTM_ZONE0 31
#define NAV_LAT0 434622300 /* 1e7deg */
#define NAV_LON0 12728900 /* 1e7deg */
#define NAV_ALT0 0 /* cm from msl */
#define NAV_HMSL0 5185 /* cm, msl from ellipsoid (EGM96) */
#define QFU 0.0
#define WP_dummy 0
#define WP_HOME 1
#define WP_STDBY 2
#define WP_1 3
#define WP_2 4
#define WP_MOB 5
#define WP_S1 6
#define WP_S2 7
#define WP_AF 8
#define WP_TD 9
#define WP__BASELEG 10
#define WP_CLIMB 11
#define WAYPOINTS { \
 {42.0, 42.0, 75},\
 {0.0, 0.0, 75},\
 {49.5, 100.1, 75},\
 {10.1, 189.9, 75},\
 {132.3, 139.1, 75},\
 {137.0, -11.6, 75},\
 {-119.2, 69.6, 75},\
 {274.4, 209.5, 75},\
 {177.4, 45.1, 30.0},\
 {28.8, 57.0, 0.0},\
 {168.8, -13.8, 75},\
 {-114.5, 162.3, 75},\
};
#define WAYPOINTS_LLA { \
 {434626158, 12733981, 7500}, /* 1e7deg, 1e7deg, cm (hmsl=51.85m) */ \
 {434622299, 12728900, 7500}, /* 1e7deg, 1e7deg, cm (hmsl=51.85m) */ \
 {434631401, 12734759, 7500}, /* 1e7deg, 1e7deg, cm (hmsl=51.85m) */ \
 {434639410, 12729661, 7500}, /* 1e7deg, 1e7deg, cm (hmsl=51.85m) */ \
 {434635066, 12744890, 7500}, /* 1e7deg, 1e7deg, cm (hmsl=51.85m) */ \
 {434621511, 12745857, 7500}, /* 1e7deg, 1e7deg, cm (hmsl=51.85m) */ \
 {434628341, 12713992, 7500}, /* 1e7deg, 1e7deg, cm (hmsl=51.85m) */ \
 {434641667, 12762269, 7500}, /* 1e7deg, 1e7deg, cm (hmsl=51.85m) */ \
 {434626690, 12750704, 3000}, /* 1e7deg, 1e7deg, cm (hmsl=51.85m) */ \
 {434627483, 12732312, 0}, /* 1e7deg, 1e7deg, cm (hmsl=51.85m) */ \
 {434621372, 12749792, 7500}, /* 1e7deg, 1e7deg, cm (hmsl=51.85m) */ \
 {434636693, 12714335, 7500}, /* 1e7deg, 1e7deg, cm (hmsl=51.85m) */ \
};
#define NB_WAYPOINT 12
#define NB_BLOCK 17
#define GROUND_ALT 0.
#define GROUND_ALT_CM 0
#define SECURITY_HEIGHT 25.
#define SECURITY_ALT 25.
#define MAX_DIST_FROM_HOME 1500.
#ifdef NAV_C

static inline void auto_nav(void) {
  switch (nav_block) {
    Block(0) // Wait GPS
    ; // pre_call
    switch(nav_stage) {
      Stage(0)
        kill_throttle = 1;
        NextStageAndBreak();
        break;
      Label(while_1)
      Stage(1)
        if (! (!(GpsFixValid()))) Goto(endwhile_2) else NextStageAndBreak();
        Stage(2)
          Goto(while_1)
        Label(endwhile_2)
      Stage(3)
        NextBlock();
        break;
    }
    ; // post_call
    break;

    Block(1) // Geo init
    ; // pre_call
    switch(nav_stage) {
      Label(while_3)
      Stage(0)
        if (! (LessThan(NavBlockTime(),10))) Goto(endwhile_4) else NextStageAndBreak();
        Stage(1)
          Goto(while_3)
        Label(endwhile_4)
      Stage(2)
        if (! (NavSetGroundReferenceHere()))
          NextStageAndBreak();
        break;
      Stage(3)
        NextBlock();
        break;
    }
    ; // post_call
    break;

    Block(2) // Holding point
    ; // pre_call
    switch(nav_stage) {
      Stage(0)
        kill_throttle = 1;
        NextStageAndBreak();
        break;
      Stage(1)
        {
          NavAttitude(RadOfDeg(0));
          NavVerticalAutoThrottleMode(RadOfDeg(0.000000));
          NavVerticalThrottleMode(9600*(0));
        }
        break;
      Stage(2)
        NextBlock();
        break;
    }
    ; // post_call
    break;

    Block(3) // Takeoff
    ; // pre_call
    if ((nav_block != 4) && (estimator_z>(ground_alt+25))) { GotoBlock(4); return; }
    switch(nav_stage) {
      Stage(0)
        kill_throttle = 0;
        NextStageAndBreak();
        break;
      Stage(1)
        estimator_flight_time = 0;
        NextStageAndBreak();
        break;
      Stage(2)
        if (NavApproachingFrom(11,1,CARROT)) NextStageAndBreakFrom(11) else {
          NavGotoWaypoint(11);
          NavVerticalAutoThrottleMode(RadOfDeg(15));
          NavVerticalThrottleMode(9600*(1.000000));
        }
        break;
      Stage(3)
        NextBlock();
        break;
    }
    ; // post_call
    break;

    Block(4) // Standby
    ; // pre_call
    switch(nav_stage) {
      Stage(0)
        NavVerticalAutoThrottleMode(RadOfDeg(0.000000));
        NavVerticalAltitudeMode(WaypointAlt(2), 0.);
        NavCircleWaypoint(2, nav_radius);
        break;
      Stage(1)
        NextBlock();
        break;
    }
    ; // post_call
    break;

    Block(5) // Figure 8 around wp 1
    ; // pre_call
    switch(nav_stage) {
      Stage(0)
        nav_eight_init();
        NextStageAndBreak();
      Stage(1)
        NavVerticalAutoThrottleMode(RadOfDeg(0.000000));
        NavVerticalAltitudeMode(WaypointAlt(3), 0.);
        Eight(3, 4, nav_radius);
        break;
      Stage(2)
        NextBlock();
        break;
    }
    ; // post_call
    break;

    Block(6) // Oval 1-2
    ; // pre_call
    switch(nav_stage) {
      Stage(0)
        nav_oval_init();
        NextStageAndBreak();
      Stage(1)
        NavVerticalAutoThrottleMode(RadOfDeg(0.000000));
        NavVerticalAltitudeMode(WaypointAlt(3), 0.);
        Oval(3, 4, nav_radius);
        break;
      Stage(2)
        NextBlock();
        break;
    }
    ; // post_call
    break;

    Block(7) // MOB
    ; // pre_call
    switch(nav_stage) {
      Stage(0)
        if (! (NavSetWaypointHere(WP_MOB)))
          NextStageAndBreak();
        break;
      Stage(1)
        nav_radius = DEFAULT_CIRCLE_RADIUS;
        NextStageAndBreak();
        break;
      Stage(2)
        NavVerticalAutoThrottleMode(RadOfDeg(0.000000));
        NavVerticalAltitudeMode(WaypointAlt(5), 0.);
        NavCircleWaypoint(5, nav_radius);
        break;
      Stage(3)
        NextBlock();
        break;
    }
    ; // post_call
    break;

    Block(8) // Line 1-2
    ; // pre_call
    if ((nav_block != 4) && (datalink_time>22)) { GotoBlock(4); return; }
    switch(nav_stage) {
      Stage(0)
        if (! (nav_line_init()))
          NextStageAndBreak();
        break;
      Stage(1)
        if (! (nav_line(WP_1, WP_2, nav_radius)))
          NextStageAndBreak();
        break;
      Stage(2)
        NextBlock();
        break;
    }
    ; // post_call
    break;

    Block(9) // Survey S1-S2
    ; // pre_call
    switch(nav_stage) {
      Stage(0)
        NavSurveyRectangleInit(6, 7, 150, NS);
        NextStageAndBreak();
      Stage(1)
        NavSurveyRectangle(6, 7);
        break;
      Stage(2)
        NextBlock();
        break;
    }
    ; // post_call
    break;

    Block(10) // Path 1,2,S1,S2,STDBY
    ; // pre_call
    switch(nav_stage) {
      Stage(0)
        if (NavApproachingFrom(4,3,CARROT)) NextStageAndBreakFrom(4) else {
          NavSegment(3, 4);
          NavVerticalAutoThrottleMode(RadOfDeg(0.000000));
          NavVerticalAltitudeMode(WaypointAlt(4), 0.);
        }
        break;
      Stage(1)
        if (NavApproachingFrom(6,4,CARROT)) NextStageAndBreakFrom(6) else {
          NavSegment(4, 6);
          NavVerticalAutoThrottleMode(RadOfDeg(0.000000));
          NavVerticalAltitudeMode(WaypointAlt(6), 0.);
        }
        break;
      Stage(2)
        if (NavApproachingFrom(7,6,1)) NextStageAndBreakFrom(7) else {
          NavSegment(6, 7);
          NavVerticalAutoPitchMode(9600*(0.400000));
          NavVerticalAltitudeMode(WaypointAlt(7), 0.);
        }
        break;
      Stage(3)
        if (NavApproachingFrom(2,7,1)) NextStageAndBreakFrom(2) else {
          NavSegment(7, 2);
          NavVerticalAutoPitchMode(9600*(0.400000));
          NavVerticalAltitudeMode(WaypointAlt(2), 0.);
        }
        break;
      Stage(4)
        GotoBlock(4);
        break;
      Stage(5)
        NextBlock();
        break;
    }
    ; // post_call
    break;

    Block(11) // Land Right AF-TD
    ; // pre_call
    switch(nav_stage) {
      Stage(0)
        nav_radius = DEFAULT_CIRCLE_RADIUS;
        NextStageAndBreak();
        break;
      Stage(1)
        GotoBlock(13);
        break;
      Stage(2)
        NextBlock();
        break;
    }
    ; // post_call
    break;

    Block(12) // Land Left AF-TD
    ; // pre_call
    switch(nav_stage) {
      Stage(0)
        nav_radius = -(DEFAULT_CIRCLE_RADIUS);
        NextStageAndBreak();
        break;
      Stage(1)
        GotoBlock(13);
        break;
      Stage(2)
        NextBlock();
        break;
    }
    ; // post_call
    break;

    Block(13) // land
    ; // pre_call
    switch(nav_stage) {
      Stage(0)
        if (! (nav_compute_baseleg(WP_AF, WP_TD, WP__BASELEG, nav_radius)))
          NextStageAndBreak();
        break;
      Stage(1)
        NavVerticalAutoThrottleMode(RadOfDeg(0.000000));
        NavVerticalAltitudeMode(WaypointAlt(10), 0.);
        NavCircleWaypoint(10, nav_radius);
        if ((NavCircleCount()>0.500000)) NextStageAndBreak();
        break;
      Stage(2)
        NavVerticalAutoThrottleMode(RadOfDeg(0.000000));
        NavVerticalAltitudeMode(WaypointAlt(10), 0.);
        NavCircleWaypoint(10, nav_radius);
        if (And(NavQdrCloseTo((DegOfRad(baseleg_out_qdr)-10)),(10>fabs((estimator_z-WaypointAlt(WP__BASELEG)))))) NextStageAndBreak();
        break;
      Stage(3)
        NextBlock();
        break;
    }
    ; // post_call
    break;

    Block(14) // final
    ; // pre_call
    if ((nav_block != 15) && ((ground_alt+10)>estimator_z)) { GotoBlock(15); return; }
    switch(nav_stage) {
      Stage(0)
        if (NavApproachingFrom(9,8,CARROT)) NextStageAndBreakFrom(9) else {
          NavSegment(8, 9);
          NavVerticalAutoThrottleMode(RadOfDeg(0.000000));
          NavGlide(8, 9);
        }
        break;
      Stage(1)
        NextBlock();
        break;
    }
    ; // post_call
    break;

    Block(15) // flare
    ; // pre_call
    switch(nav_stage) {
      Stage(0)
        if (NavApproachingFrom(9,8,0)) NextStageAndBreakFrom(9) else {
          NavSegment(8, 9);
          NavVerticalAutoThrottleMode(RadOfDeg(0.000000));
          NavVerticalThrottleMode(9600*(0.000000));
        }
        break;
      Stage(1)
        if (FALSE) NextStageAndBreak() else {
          NavAttitude(RadOfDeg(0.000000));
          NavVerticalAutoThrottleMode(RadOfDeg(0.000000));
          NavVerticalThrottleMode(9600*(0.000000));
        }
        break;
      Stage(2)
        NextBlock();
        break;
    }
    ; // post_call
    break;

    Block(16) // HOME
    ; // pre_call
    switch(nav_stage) {
      Stage(0)
        nav_home();
        break;
      Stage(1)
        NextBlock();
        break;
    }
    ; // post_call
    break;

  }
}
#endif // NAV_C

#endif // FLIGHT_PLAN_H
