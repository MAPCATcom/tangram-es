#include "mapInit.h"
#include <sstream>
#include <rapidjson/document.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <memory>
#include "tangram.h"

using namespace std;

LayerOptions::LayerOptions(bool _cycleRoad,
                           bool _cycleRoute) :
    cycleRoad(_cycleRoad),
    cycleRoute(_cycleRoute)
{}

MapInit::MapInit(shared_ptr<Tangram::Platform> _platform,
                 const string& _apiUrl) :
    platform(_platform),
    apiUrl(_apiUrl)
{}

void MapInit::initVectorView(function<void(Tangram::UrlResponse)> callback,
                             const string& apiKey,
                             const LayerOptions& layerOptions) {
    rapidjson::Document postData;
    rapidjson::Value sources;
    sources.SetObject();
    sources.AddMember("base", "", postData.GetAllocator());
    sources.AddMember("ocean", "", postData.GetAllocator());
    sources.AddMember("relief", "", postData.GetAllocator());
    sources.AddMember("landcover", "", postData.GetAllocator());
    if (layerOptions.cycleRoad || layerOptions.cycleRoute) {
        sources.AddMember("cycle", "", postData.GetAllocator());
        if (!layerOptions.cycleRoad) {
            sources["cycle"] = "--,route";
        } else if (!layerOptions.cycleRoute) {
            sources["cycle"] = "--,road";
        }
    }

    postData.SetObject();
    postData.AddMember("layers", sources, postData.GetAllocator());
    postData.AddMember("type", 3, postData.GetAllocator());

    ostringstream oss;
    rapidjson::OStreamWrapper osw(oss);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    postData.Accept(writer);
    string postDataString = oss.str();

    string url = apiUrl + "/api/mapinit/vector?api_key=" + apiKey;
    platform->startUrlRequest(Tangram::Url(url), callback, postDataString);
}
