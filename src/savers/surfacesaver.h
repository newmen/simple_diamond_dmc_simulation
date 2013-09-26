#ifndef SURFACESAVER_H
#define SURFACESAVER_H

#include "../surface/surface.h"
#include "timenumbercurvessaver.h"

class SurfaceSaver : public TimeNumberCurvesSaver
{
public:
    SurfaceSaver(const char *outFileName, Surface *surface);
    void save(double time);

private:
    Surface *_surface;
};

#endif // SURFACESAVER_H
