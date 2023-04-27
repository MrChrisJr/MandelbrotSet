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

void ComplexPlane :: setMouseLocation(Vector2f coord)
{
    m_mouseLocation = coord;
}

void ComplexPlane :: loadText(Text& text)
{
    stringstream output;
    output << "Mandelbrot Set" << endl
           << "Center: " << "(" << getCenter().x
           << "," << getCenter().y << ")" << endl
           << "Cursor: " << "(" << m_mouseLocation.x
           << "," << m_mouseLocation.y << ")" << endl
           << "Left-click to Zoom in" << endl
           << "Right-click to Zoom in" << endl;
    text.setString(output.str());
}