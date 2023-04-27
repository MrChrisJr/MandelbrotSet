#ifndef COMPLEXPLANE_H
#define COMPLEXPLANE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <cmath>
#include <complex>

using namespace sf;
using namespace std;


    const unsigned int MAX_ITER = 64;
    const float BASE_WIDTH = 4.0;
    const float BASE_HEIGHT = 4.0;
    const float BASE_ZOOM = 0.5;


class ComplexPlane : public View
{
    private:
        Vector2f m_mouseLocation;
        View m_view;
        int m_zoomCount;
        float m_aspectRatio;
    public:
        ComplexPlane(float aspectRatio);
        void zoomIn();
        void zoomOut();
        void setCenter(Vector2f coord);
        View getView();
        void setMouseLocation(Vector2f coord);
        void loadText(Text& Text);
        static size_t countIterations(Vector2f coord);
        static void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b); 

};

#endif