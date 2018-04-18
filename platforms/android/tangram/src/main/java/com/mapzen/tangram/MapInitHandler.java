package com.mapzen.tangram;

import java.util.ArrayList;

public class MapInitHandler {
    static ArrayList<MapInitListener> listeners = new ArrayList<>();
    public static void registerListener(MapInitListener listener) {
        for (int i = 0; i < listeners.size(); ++i) {
            if (listeners.get(i) == listener) {
                return;
            }
        }
        listeners.add(listener);
    }
    public static void unregisterListener(MapInitListener listener) {
        for (int i = 0; i < listeners.size(); ++i) {
            if (listeners.get(i) == listener) {
                listeners.remove(listener);
                return;
            }
        }
    }
    public static void onError(String error) {
        for (int i = 0; i < listeners.size(); ++i) {
            listeners.get(i).onMapInitError(error);
        }
    }
    public static void onSuccess(String style) {
        for (int i = 0; i < listeners.size(); ++i) {
            listeners.get(i).onMapInitSuccess(style);
        }
    }
}