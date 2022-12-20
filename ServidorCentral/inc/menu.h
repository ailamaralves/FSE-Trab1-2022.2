#include <bcm2835.h>
#include <utility>
#include <fstream>
#include <string>
#include <ncurses.h>
#include <json.h>
#include<unistd.h>

#define OFFLINEVALUE 0xff

#define CLIENT_IP "0.0.0.0"
#define SERVER_PORT 10080
#define CLIENT_PORT 10180

//helpers
#define repeat(x) for(int it=0;it<x;it++)

void* menu(void *arg);
int handle_keypress(char c, uint8_t* state);

using json = nlohmann::json;

class SensorWindow 
{
private:
    int state;
    std::string type;
    std::string tag;
    int gpioPin;
    WINDOW * win;
public:
    std::pair<int,int> yx;
    SensorWindow(json sensor, std::pair<int,int> pyx);
    void refreshIt(int state);
};

class MenuWindow
{
public:
    int states[15];
    SensorWindow* light1;
    SensorWindow* light2;
    SensorWindow* air;
    SensorWindow* projector;
    SensorWindow* alarmBuzz;
    SensorWindow* sPresence;
    SensorWindow* sSmoke;
    SensorWindow* sWindow;
    SensorWindow* sDoor;
    SensorWindow* sCountIn;
    SensorWindow* sCountOut;
    SensorWindow* sTempHumid;
    MenuWindow(json data);
    void refreshAll(uint8_t* states);
    void printChoices();
    void d();
};