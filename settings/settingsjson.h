#ifndef SETTINGSJSON_H
#define SETTINGSJSON_H

#include <QFile>
#include <QTextStream>
#include <string>

#include "../enums.h"
#include "../json.hpp"

using json = nlohmann::json;

class SettingsJson {
public:
    SettingsJson() {}
    ~SettingsJson() {}

    static bool saveParametresToJsonFile(SettingsJson settingsJson) {
        QFile out(FILE_PATH_TO_JSON);
        if (out.open(QIODevice::WriteOnly)) {
            QTextStream stream( &out );
            json jsonObj = {
                {"color_figure_in_bottom",          settingsJson.colorFigureInBottom},
                {"min_on_timer",                    settingsJson.minOnTimer},
                {"sec_on_timer",                    settingsJson.secOnTimer},
                {"figure_disposition",              settingsJson.figureDisposition},
                {"file_name_of_figure_disposition", settingsJson.fileNameOfFigureDisposition}
            };

            qDebug() << jsonObj.dump().c_str();
            stream << jsonObj.dump().c_str();
            out.close();
            return true;
        }

        return false;
    }

    static bool updateParametresFromJsonFile(SettingsJson &settingsJson) {
        if (!QFile(FILE_PATH_TO_JSON).exists()) {
            qDebug() << "first launch, update defaulted values";
            saveDefaulteParameter(settingsJson);
            return true;
        }

        QFile in(FILE_PATH_TO_JSON);
        bool resultOfUpdate = false;
        if (in.open(QIODevice::ReadOnly)) {
            QTextStream stream( &in );
            try {
                json jsonObj = json::parse(stream.readAll().toStdString());

                settingsJson.colorFigureInBottom         = jsonObj["color_figure_in_bottom"];
                settingsJson.minOnTimer                  = jsonObj["min_on_timer"];
                settingsJson.secOnTimer                  = jsonObj["sec_on_timer"];
                settingsJson.figureDisposition           = jsonObj["figure_disposition"];
                settingsJson.fileNameOfFigureDisposition = jsonObj["file_name_of_figure_disposition"];

                qDebug() << "updated values from json";

                resultOfUpdate = true;
            } catch (json::type_error e) {
                qDebug() << "type is not completable, update defaulted values";
                saveDefaulteParameter(settingsJson);
            } catch (json::parse_error e) {
                qDebug() << "parse incorrect, update defaulted values";
                saveDefaulteParameter(settingsJson);
            }

            in.close();
            return resultOfUpdate;
        } else {
            qDebug() << "file cannot open";
            return false;
        }
    }


    FigureColor colorFigureInBottom = FigureColor::WHITE;
    int minOnTimer = 15;
    int secOnTimer = 30;
    FigureDisposition figureDisposition = FigureDisposition::CLASSIC;
    std::string fileNameOfFigureDisposition = "";
    // ...

private:
    static bool saveDefaulteParameter(SettingsJson& settingsJson) {
        settingsJson = SettingsJson();
        return saveParametresToJsonFile(settingsJson);
    }

    static constexpr char FILE_PATH_TO_JSON[] = "settings.json";
};

#endif // SETTINGSJSON_H
