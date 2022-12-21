#include <pthread.h>
#include <server.h>
#include <unistd.h>
#include <utility>
#include <fstream>
#include <string>
#include <ncurses.h>
#include <json.h>


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

MenuWindow::MenuWindow(json data){
    int states[15] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    light1 = new SensorWindow(data["outputs"][0], std::pair<int,int>(0, 0));
    light2 = new SensorWindow(data["outputs"][1], std::pair<int,int>(0, 51));
    air = new SensorWindow(data["outputs"][2], std::pair<int,int>(3, 0));
    projector = new SensorWindow(data["outputs"][3], std::pair<int,int>(3, 51));
    alarmBuzz = new SensorWindow(data["outputs"][4], std::pair<int,int>(6, 0));
    sPresence = new SensorWindow(data["inputs"][0], std::pair<int,int>(6, 51));
    sSmoke = new SensorWindow(data["inputs"][1], std::pair<int,int>(9, 0));
    sWindow = new SensorWindow(data["inputs"][2], std::pair<int,int>(9, 51));
    sDoor = new SensorWindow(data["inputs"][3], std::pair<int,int>(12, 0));
    sCountIn = new SensorWindow(data["inputs"][4], std::pair<int,int>(12, 51));
    sCountOut = new SensorWindow(data["inputs"][5], std::pair<int,int>(15, 0));
    sTempHumid = new SensorWindow(data["sensor_temperatura"][0], std::pair<int,int>(15, 51));
}
void MenuWindow::refreshAll(uint8_t* states){
    start_color();
    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_GREEN, COLOR_GREEN);
    light1->refreshIt(states[0]);
    light2->refreshIt(states[1]);
    air->refreshIt(states[2]);
    projector->refreshIt(states[3]);
    alarmBuzz->refreshIt(states[4]);
    sPresence->refreshIt(states[5]);
    sSmoke->refreshIt(states[6]);
    sWindow->refreshIt(states[7]);
    sDoor->refreshIt(states[8]);
    sCountIn->refreshIt(states[9]);
    sCountOut->refreshIt(states[10]);
    sTempHumid->refreshIt(states[11]);
}

void MenuWindow::d(){
    delete light1;
    delete light2;
    delete air;
    delete projector;
    delete alarmBuzz;
    delete sPresence;
    delete sSmoke;
    delete sWindow;
    delete sDoor;
    delete sCountIn;
    delete sCountOut;
    delete sTempHumid;
}

SensorWindow::SensorWindow(json sensor, std::pair<int,int> pyx){
    SensorWindow::type = sensor["type"];
    SensorWindow::tag = sensor["tag"];
    SensorWindow::gpioPin = sensor["gpio"];
    SensorWindow::state = OFFLINEVALUE;
    SensorWindow::yx = pyx;
    SensorWindow::win = newwin(3, 50, yx.first, yx.second);
    refresh();
    mvwprintw(win, 1, 1, "%s: ", tag.data());
    wrefresh(win);
}

void SensorWindow::refreshIt(int state){
    SensorWindow::state = state;
    wattron(win, COLOR_PAIR((state? 2 : 1)));
    if(type == "dth22"){
        mvwprintw(win, 1, tag.size()+3, "%d", state);
    }else{
        mvwprintw(win, 1, tag.size()+3, (state? "On " : "Off"));
    }
    wattroff(win, COLOR_PAIR((state? 2 : 1)));

    wrefresh(win);
}

int handle_keypress(char c, uint8_t* state){
    switch (c)
    {
    case '1':
        state[1] = (state[1]? 0 : 1);
        break;

    case '2':
        state[2] = (state[2]? 0 : 1);
        break;

    case '3':
        state[3] = (state[3]? 0 : 1);
        break;

    case '4':
        state[4] = (state[4]? 0 : 1);
        break;

    case '5':
        state[5] = (state[5]? 0 : 1);
        break;

    case '0':
        return 1;
        
    default:
        break;
    }
    return 0;
}

void* menu(void *arg){
    initscr();

    std::ifstream f("sala_01.json");
    json data = json::parse(f);
    char c = 0;
    uint8_t* response = (uint8_t*)arg;
    MenuWindow main_menu(data);
    move(18, 0);
    WINDOW* commWin = newwin(3, 100, 18, 0);
    refresh();
    mvwprintw(commWin, 1, 1, "Digite uma opção (de 1 a 5) caso queira alterar os estados.");
    wrefresh(commWin);
    while(1){
        refresh();
        move(21, 0);
        char c = getch();
        if(handle_keypress(c, response)){
            break;
        }
        main_menu.refreshAll(response);
    }
    endwin();

    main_menu.d();
    return NULL;
}
