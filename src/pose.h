struct vec3 {
    float x, y, z;
};

class Pose {
    public:
        vec3 pos;
        vec3 vel;
        vec3 acc;
        vec3 orientation;
};
