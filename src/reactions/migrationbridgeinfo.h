#ifndef MIGRATIONBRIDGEINFO_H
#define MIGRATIONBRIDGEINFO_H

#include "../int3.h"
#include "../surface/carbon.h"
#include <utility>

class MigrationBridgeInfo
{
public:
    MigrationBridgeInfo(const int3 &position, const std::pair<Carbon *, Carbon *> &toBasis);
    int3 position();
    std::pair<Carbon *, Carbon *> toBasis();

private:
    int3 _position;
    std::pair<Carbon *, Carbon *> _toBasis;
};

#endif // MIGRATIONBRIDGEINFO_H
