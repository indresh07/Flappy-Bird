#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

namespace gameEngine{

    struct Position{
        float x;
        float y;
    };

    struct Color{
        float r;
        float g;
        float b;
        float a;
    };

    struct UV{
        float u;
        float v;
    };

    struct vertex{
        Position position;

        Color color;

        UV uv;

        void setVertex(float r, float g, float b, float a, float x, float y, float u, float v ){
            color.r = r;
            color.g = g;
            color.b = b;
            color.a = a;
            position.x = x;
            position.y = y;
            uv.u = u;
            uv.v = v;
        }

    };
}

#endif // SHADER_H_INCLUDED
