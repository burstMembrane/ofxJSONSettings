#pragma once

#include "ofMain.h"

class ofxJSONSettings : public ofBaseApp {

public:
  void loadSettings(string filePath);
  void saveSettings(string filePath);
  void loadNetworkSettings(string url, string savePath);

  bool areSettingsLoaded();
  //   getting values
  int getIntValue(string jsonKey);
  bool getBoolValue(string jsonKey);
  string getStringValue(string jsonKey);
  float getFloatValue(string jsonKey);
  vector<int> getIntArray(string jsonKey);
  vector<string> getStringArray(string jsonKey);
  vector<float> getFloatArray(string jsonKey);
  void checkType(string jsonKey);

  //   setting values
  void addStringValue(string key, string value);
  void addIntValue(string key, int value);
  void addFloatValue(string key, float value);
  void addBoolValue(string key, bool value);

protected:
  ofJson settings;
  string settingsPath;
  bool isLoaded;
};
