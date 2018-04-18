package com.mapzen.tangram;

public interface MapInitListener {
    void onMapInitError(String error);
    void onMapInitSuccess(String error);
}
