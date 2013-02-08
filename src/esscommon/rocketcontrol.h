#ifndef _ROCKETCONTROL_H
#define _ROCKETCONTROL_H 1

/// Each engine control value should be in the range 0..1 and values outside
/// this will be clamped.  The rocket class itself defines how much power each
/// engine is capable of producing.
struct RocketControl {
    public:
    static const int NUM_ENGINES = 8;
    
    union {
        float engine[NUM_ENGINES];
        struct __attribute__((__packed__)) {
            // The Main Engines point down.  1 and 2 are opposite each other
            // as are 3 and 4.
            float main1;    // Main engine 1
            float main2;    // Main engine 2
            float main3;    // Main engine 3
            float main4;    // Main engine 4

            // The Rotational engines can act to spin the rocket on its axis,
            // or to push it.  1 and 2 act to spin the rocket clock-wise
            // (looking down), 1 and 4 act to push it.
            //
            // The Rotational Engines are carefully placed on the rocket to
            // act on the plane of its center of mass so they don't also cause
            // tipping.
            float rot1;     // Rotational engine 1
            float rot2;     // Rotational engine 2
            float rot3;     // Rotational engine 2
            float rot4;     // Rotational engine 2
        } name;
    };
};
#endif
