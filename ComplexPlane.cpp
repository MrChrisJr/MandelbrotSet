#include "ComplexPlane.h"

ComplexPlane :: ComplexPlane(float aspectRatio)
{
    m_aspectRatio = aspectRatio;
    m_view.setSize(BASE_WIDTH,-BASE_HEIGHT * m_aspectRatio);
    m_view.setCenter(0.0,0.0);
    m_zoomCount = 0;
}

void ComplexPlane :: zoomIn()
{
    m_zoomCount++;
    float x = BASE_WIDTH * (pow(BASE_ZOOM,m_zoomCount));
    float y = BASE_HEIGHT * m_aspectRatio *(pow(BASE_ZOOM,m_zoomCount));
    m_view.setSize(x,y);
}

void ComplexPlane :: zoomOut()
{
    m_zoomCount--;
    float x = BASE_WIDTH * (pow(BASE_ZOOM,m_zoomCount));
    float y = BASE_HEIGHT * m_aspectRatio *(pow(BASE_ZOOM,m_zoomCount));
    m_view.setSize(x,y);
}

void ComplexPlane :: setCenter(Vector2f coord)
{
    m_view.setCenter(coord);
}

View ComplexPlane :: getView()
{
    return m_view;
}

void ComplexPlane :: setMouseLocation(Vector2f coord)
{
    m_mouseLocation = coord;
}

void ComplexPlane :: loadText(Text& text)
{
    stringstream output;
    output << "Mandelbrot Set" << endl
           << "Center: " << "(" << m_view.getCenter().x
           << "," << m_view.getCenter().y << ")" << endl
           << "Cursor: " << "(" << m_mouseLocation.x
           << "," << m_mouseLocation.y << ")" << endl
           << "Left-click to Zoom in" << endl
           << "Right-click to Zoom out" << endl;
    text.setString(output.str());
}

size_t ComplexPlane :: countIterations(Vector2f coord)
{
    size_t iters = 0;
    int x = coord.x;
    int y = coord.y;
    complex<double> c (x,y);
    complex<double> z (0,0);
    while(iters <= MAX_ITER)
    {
        z = z*z + c;
        iters++;
        if(abs(z) > 2.0 || abs(c) > 2.0)
        {
            return iters;
        }
    }
    return MAX_ITER;
}

void ComplexPlane :: iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
    if(count != MAX_ITER)
    {
        r = count;
        g = count;
        b = count;
    }
    else if(count == MAX_ITER)
    {
        r = 255;
        g = 0;
        b = 255;
    }
}