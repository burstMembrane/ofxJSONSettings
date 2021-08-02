#include "ofxJSONSettings.h"

void ofxJSONSettings::loadNetworkSettings(string url, string savePath) {
  // load settings from network
  ofHttpResponse resp = ofLoadURL(url);
  if (resp.status == 200) {
    ofLogNotice("ofxJSONSettings") << "received data: \n" << resp.data << "\n";
    // for now save json then load it in as settings
    // TODO: serialize json directly from response?
    ofSaveURLTo(url, savePath);
    loadSettings(savePath);
    settingsPath = savePath;
    isLoaded = true;
  } else {
    isLoaded = false;
    ofLogError("ofxJSONSettings")
        << "Couldnt retrieve data from " << url << "\n";
  }
}
void ofxJSONSettings::loadSettings(string filePath) {
  // load settings from local json
  settingsPath = filePath;
  ofFile file(filePath);
  if (file.exists()) {
    settings = ofLoadJson(filePath);
    ofLogNotice("ofxJSONSettings") << "Found JSON file " << filePath << " with "
                                   << settings.size() << " entries" << endl;

    ofLogNotice("ofxJSONSettings") << settings << endl;
    isLoaded = true;
  } else {
    ofLogError("ofxJSONSettings") << "Couldn't find " << filePath
                                  << "in data folder. \n Please create a JSON "
                                     "settings file and restart \n";
    isLoaded = false;
  }
}

bool ofxJSONSettings::areSettingsLoaded() {
  // check if settings are loaded
  return isLoaded;
}

int ofxJSONSettings::getIntValue(string key) {
  // get int value from loaded json
  for (auto &entry : settings.items()) {
    if (entry.key() == key) {
      ofLogVerbose("ofxJSONSettings")
          << "Found value for key:  " << key << " : " << entry.value() << "\n";
      if (settings[key].is_number())
        return entry.value();
    }
  }
  ofLogError("ofxJSONSettings")
      << "Couldnt find value for key:  " << key << "\n";
  return 0;
}

bool ofxJSONSettings::getBoolValue(string key) {
  // get boolean value from loaded json
  for (auto &entry : settings.items()) {
    if (entry.key() == key) {
      ofLogVerbose("ofxJSONSettings")
          << "Found value for key:  " << key << " : " << entry.value() << "\n";
      if (settings[key].is_boolean())
        return entry.value();
    }
  }
  //   defaults to false
  ofLogError("ofxJSONSettings")
      << "Couldnt find value for key:  " << key << "\n";
  return false;
}

string ofxJSONSettings::getStringValue(string key) {
  //   get a string value from the loaded json
  for (auto &entry : settings.items()) {
    if (entry.key() == key) {
      ofLogVerbose("ofxJSONSettings")
          << "Found value for key:  " << key << " : " << entry.value() << "\n";
      if (settings[key].is_string())
        return entry.value();
    }
  }
  //   defaults to empty string
  ofLogError("ofxJSONSettings")
      << "Couldnt find value for key:  " << key << "\n";
  return "";
}

float ofxJSONSettings::getFloatValue(string key) {
  // get a float value from the loaded json
  for (auto &entry : settings.items()) {
    if (entry.key() == key) {
      ofLogVerbose("ofxJSONSettings")
          << "Found value for key:  " << key << " : " << entry.value() << "\n";
      if (settings[key].is_number_float())
        return entry.value();
    }
  }
  //   defaults to empty string
  ofLogError("ofxJSONSettings")
      << "Couldnt find value for key:  " << key << "\n";
  return 0.0;
}

vector<int> ofxJSONSettings::getIntArray(string key) {
  // get int array from settings json
  vector<int> intArray;
  for (auto &entry : settings.items()) {
    if (entry.key() == key) {

      if (settings[key].is_array()) {
        intArray.resize(settings[key].size());

        ofLogVerbose("ofxJSONSettings") << "Found array value for key:  " << key
                                        << " : " << entry.value() << "\n";
        for (size_t i = 0; i < settings[key].size(); i++) {
          if (settings[key][i].is_number())
            intArray.at(i) = settings[key][i];
          /* code */
        }
        return intArray;
      }
    }
  }
  ofLogError("ofxJSONSettings")
      << "Couldnt find value for key:  " << key << "\n";
  return intArray;
}

vector<string> ofxJSONSettings::getStringArray(string key) {
  // get string array from settings json
  vector<string> strArray;
  for (auto &entry : settings.items()) {
    if (entry.key() == key) {
      if (settings[key].is_array()) {
        strArray.resize(settings[key].size());
        ofLogVerbose("ofxJSONSettings") << "Found array value for key:  " << key
                                        << " : " << entry.value() << "\n";
        for (size_t i = 0; i < settings[key].size(); i++) {
          if (settings[key][i].is_string())
            strArray.at(i) = settings[key][i];
          /* code */
        }
        return strArray;
      }
    }
  }
  ofLogError("ofxJSONSettings")
      << "Couldnt find string array for key:  " << key << "\n";
  return strArray;
}

vector<float> ofxJSONSettings::getFloatArray(string key) {
  // get float array from settings json
  vector<float> floArray;
  for (auto &entry : settings.items()) {
    if (entry.key() == key) {
      if (settings[key].is_array()) {
        floArray.resize(settings[key].size());
        ofLogVerbose("ofxJSONSettings") << "Found array value for key:  " << key
                                        << " : " << entry.value() << "\n";
        for (size_t i = 0; i < settings[key].size(); i++) {
          if (settings[key][i].is_number_float())
            floArray.at(i) = settings[key][i];
        }
        return floArray;
      }
    }
  }
  ofLogError("ofxJSONSettings")
      << "Couldnt find string array for key:  " << key << "\n";
  return floArray;
}
void ofxJSONSettings::addStringValue(string key, string value) {
  // add string value to settings json
  ofLogVerbose("ofxJSONSettings")
      << "adding entry "
      << "{" << key << ":" << ofToString(value) << "} \n";
  settings.emplace(key, value);
  ofLogVerbose("ofxJSONSettings") << settings << endl;
}

void ofxJSONSettings::addIntValue(string key, int value) {
  // add int value to settings json
  ofLogVerbose("ofxJSONSettings")
      << "adding entry "
      << "{" << key << ":" << ofToString(value) << "} \n";
  settings.emplace(key, value);
  ofLogVerbose("ofxJSONSettings") << settings << endl;
}
void ofxJSONSettings::saveSettings(string filePath) {
  // if the settings aren't empty save em...
  if (filePath.length() == 0) {
    //   default to overwriting loaded settings
    filePath = settingsPath;
  }
  if (!settings.empty()) {
    ofLogNotice("ofxJSONSettings") << "Saving settings to " << filePath << "\n";
    ofSavePrettyJson(filePath, settings);
  }
}