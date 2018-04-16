#pragma once

#include <memory>
#include "platform.h"

const std::string MAPCAT_API_URL = "https://api.mapcat.com";

// forward declaration
namespace Tangram {
    class Platform;
}

struct LayerOptions {
    LayerOptions(bool _cycleRoad = false,
                 bool _cycleRoute = false);
    bool cycleRoad = false;
    bool cycleRoute = false;
};

class MapInit {
public:
    MapInit(std::shared_ptr<Tangram::Platform> _platform,
            const std::string& _apiUrl = MAPCAT_API_URL);
    void initVectorView(std::function<void(Tangram::UrlResponse)> callback,
                        const std::string& apiKey,
                        const LayerOptions& layerOptions);

private:
    std::shared_ptr<Tangram::Platform> platform;
    std::string apiUrl;
};
