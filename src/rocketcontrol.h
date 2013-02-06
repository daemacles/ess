
/// Each engine control value should be in the range 0..1 and values outside
/// this will be clamped.  The rocket class itself defines how much power each
/// engine is capable of producing.
struct RocketControl {
    public:
    static const int NUM_ENGINES = 8;
    
    union {
        btScalar engine[NUM_ENGINES];
        struct __attribute__((__packed__)) {
            // The Main Engines point down.  1 and 2 are opposite each other
            // as are 3 and 4.
            btScalar main1;    // Main engine 1
            btScalar main2;    // Main engine 2
            btScalar main3;    // Main engine 3
            btScalar main4;    // Main engine 4

            // The Rotational engines can act to spin the rocket on its axis,
            // or to push it.  1 and 2 act to spin the rocket clock-wise
            // (looking down), 1 and 4 act to push it.
            //
            // The Rotational Engines are carefully placed on the rocket to
            // act on the plane of its center of mass so they don't also cause
            // tipping.
            btScalar rot1;     // Rotational engine 1
            btScalar rot2;     // Rotational engine 2
            btScalar rot3;     // Rotational engine 2
            btScalar rot4;     // Rotational engine 2
        } name;
    };
};
