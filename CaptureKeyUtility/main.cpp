#include <libevdev/libevdev.h>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <cstring>
#include <string>
#include <chrono>
#include <cmath>
#include <fstream>
#include <unordered_set>
#include <map>
#include <list>
#include <vector>
#include <array>
#include <unordered_map>
#include <filesystem>

#include <yaml-cpp/yaml.h>

//Карта имён клавиш и их кодов в библиотеке libevdev
std::map<std::string, int> stringsAndKeyCodesMap{   {"Esc", KEY_ESC},
                                                    {"1", KEY_1},
                                                    {"2", KEY_2},
                                                    {"3", KEY_3},
                                                    {"4", KEY_4},
                                                    {"5", KEY_5},
                                                    {"6", KEY_6},
                                                    {"7", KEY_7},
                                                    {"8", KEY_8},
                                                    {"9", KEY_9},
                                                    {"0", KEY_0},
                                                    {"-", KEY_MINUS},
                                                    {"+", KEY_EQUAL},
                                                    {"Backspace", KEY_BACKSPACE},
                                                    {"Tab", KEY_TAB},
                                                    {"q", KEY_Q},
                                                    {"Q", KEY_Q},
                                                    {"w", KEY_W},
                                                    {"W", KEY_W},
                                                    {"e", KEY_E},
                                                    {"E", KEY_E},
                                                    {"r", KEY_R},
                                                    {"R", KEY_R},
                                                    {"t", KEY_T},
                                                    {"T", KEY_T},
                                                    {"y", KEY_Y},
                                                    {"Y", KEY_Y},
                                                    {"u", KEY_U},
                                                    {"U", KEY_U},
                                                    {"i", KEY_I},
                                                    {"I", KEY_I},
                                                    {"o", KEY_O},
                                                    {"O", KEY_O},
                                                    {"p", KEY_P},
                                                    {"P", KEY_P},
                                                    {"[", KEY_LEFTBRACE},
                                                    {"]", KEY_RIGHTBRACE},
                                                    {"Enter", KEY_ENTER},
                                                    {"Left Ctrl", KEY_LEFTCTRL},
                                                    {"a", KEY_A},
                                                    {"A", KEY_A},
                                                    {"s", KEY_S},
                                                    {"S", KEY_S},
                                                    {"d", KEY_D},
                                                    {"D", KEY_D},
                                                    {"f", KEY_F},
                                                    {"F", KEY_F},
                                                    {"g", KEY_G},
                                                    {"G", KEY_G},
                                                    {"h", KEY_H},
                                                    {"H", KEY_H},
                                                    {"j", KEY_J},
                                                    {"J", KEY_J},
                                                    {"k", KEY_K},
                                                    {"K", KEY_K},
                                                    {"l", KEY_L},
                                                    {"L", KEY_L},
                                                    {";", KEY_SEMICOLON},
                                                    {"'", KEY_APOSTROPHE},
                                                    {"`", KEY_GRAVE},
                                                    {"Left Shift", KEY_LEFTSHIFT},
                                                    {"\\", KEY_BACKSLASH},
                                                    {"z", KEY_Z},
                                                    {"Z", KEY_Z},
                                                    {"x", KEY_X},
                                                    {"X", KEY_X},
                                                    {"c", KEY_C},
                                                    {"C", KEY_C},
                                                    {"v", KEY_V},
                                                    {"V", KEY_V},
                                                    {"b", KEY_B},
                                                    {"B", KEY_B},
                                                    {"n", KEY_N},
                                                    {"N", KEY_N},
                                                    {"m", KEY_M},
                                                    {"M", KEY_M},
                                                    {",", KEY_COMMA},
                                                    {".", KEY_DOT},
                                                    {"/", KEY_SLASH},
                                                    {"Right Shift", KEY_RIGHTSHIFT},
                                                    {"*", KEY_KPASTERISK},
                                                    {"Left Alt", KEY_LEFTALT},
                                                    {"Space", KEY_SPACE},
                                                    {"Caps Lock", KEY_CAPSLOCK},
                                                    {"F1", KEY_F1},
                                                    {"F2", KEY_F2},
                                                    {"F3", KEY_F3},
                                                    {"F4", KEY_F4},
                                                    {"F5", KEY_F5},
                                                    {"F6", KEY_F6},
                                                    {"F7", KEY_F7},
                                                    {"F8", KEY_F8},
                                                    {"F9", KEY_F9},
                                                    {"F10", KEY_F10},
                                                    {"Num Lock", KEY_NUMLOCK},
                                                    {"Scroll Lock", KEY_SCROLLLOCK},
                                                    {"Numpad 7", KEY_KP7},
                                                    {"Numpad 8", KEY_KP8},
                                                    {"Numpad 9", KEY_KP9},
                                                    {"Numpad -", KEY_KPMINUS},
                                                    {"Numpad 4", KEY_KP4},
                                                    {"Numpad 5", KEY_KP5},
                                                    {"Numpad 6", KEY_KP6},
                                                    {"Numpad +", KEY_KPPLUS},
                                                    {"Numpad 1", KEY_KP1},
                                                    {"Numpad 2", KEY_KP2},
                                                    {"Numpad 3", KEY_KP3},
                                                    {"Numpad 0", KEY_KP0},
                                                    {"Numpad .", KEY_KPDOT},
                                                    {"F11", KEY_F11},
                                                    {"F12", KEY_F12},
                                                    {"Numpad Enter", KEY_KPENTER},
                                                    {"Right Ctrl", KEY_RIGHTCTRL},
                                                    {"Numpad /", KEY_KPSLASH},
                                                    {"Print Screen", KEY_SYSRQ},
                                                    {"Right Alt", KEY_RIGHTALT},
                                                    {"Home", KEY_HOME},
                                                    {"Arrow Up", KEY_UP},
                                                    {"Page Up", KEY_PAGEUP},
                                                    {"Arrow Left", KEY_LEFT},
                                                    {"Arrow Right", KEY_RIGHT},
                                                    {"End", KEY_END},
                                                    {"Arrow Down", KEY_DOWN},
                                                    {"Page Down", KEY_PAGEDOWN},
                                                    {"Insert", KEY_INSERT},
                                                    {"Delete", KEY_DELETE},
                                                    {"Pause/Break", KEY_PAUSE},
                                                    {"Left Win", KEY_LEFTMETA},
                                                    {"Left Function Key", KEY_LEFTMETA},
                                                    {"Right Win", KEY_RIGHTMETA},
                                                    {"Right Function Key", KEY_RIGHTMETA},
                                                    {"Compose", KEY_COMPOSE}
                                                };


//Карта имён клавиш и их кодов в библиотеке libevdev
std::map<int, std::string> keyCodesAndStringsMap{   {KEY_ESC, "Esc"}, 
                                                    {KEY_1, "1"}, 
                                                    {KEY_2, "2"}, 
                                                    {KEY_3, "3"}, 
                                                    {KEY_4, "4"}, 
                                                    {KEY_5, "5"}, 
                                                    {KEY_6, "6"}, 
                                                    {KEY_7, "7"}, 
                                                    {KEY_8, "8"}, 
                                                    {KEY_9, "9"}, 
                                                    {KEY_0, "0"}, 
                                                    {KEY_MINUS, "-"}, 
                                                    {KEY_EQUAL, "+"}, 
                                                    {KEY_BACKSPACE, "Backspace"}, 
                                                    {KEY_TAB, "Tab"}, 
                                                    {KEY_Q, "q"}, 
                                                    {KEY_Q, "Q"}, 
                                                    {KEY_W, "w"}, 
                                                    {KEY_W, "W"}, 
                                                    {KEY_E, "e"}, 
                                                    {KEY_E, "E"}, 
                                                    {KEY_R, "r"}, 
                                                    {KEY_R, "R"}, 
                                                    {KEY_T, "t"}, 
                                                    {KEY_T, "T"}, 
                                                    {KEY_Y, "y"}, 
                                                    {KEY_Y, "Y"}, 
                                                    {KEY_U, "u"}, 
                                                    {KEY_U, "U"}, 
                                                    {KEY_I, "i"}, 
                                                    {KEY_I, "I"}, 
                                                    {KEY_O, "o"}, 
                                                    {KEY_O, "O"}, 
                                                    {KEY_P, "p"}, 
                                                    {KEY_P, "P"}, 
                                                    {KEY_LEFTBRACE, "["}, 
                                                    {KEY_RIGHTBRACE, "]"}, 
                                                    {KEY_ENTER, "Enter"}, 
                                                    {KEY_LEFTCTRL, "Left Ctrl"}, 
                                                    {KEY_A, "a"}, 
                                                    {KEY_A, "A"}, 
                                                    {KEY_S, "s"}, 
                                                    {KEY_S, "S"}, 
                                                    {KEY_D, "d"}, 
                                                    {KEY_D, "D"}, 
                                                    {KEY_F, "f"}, 
                                                    {KEY_F, "F"}, 
                                                    {KEY_G, "g"}, 
                                                    {KEY_G, "G"}, 
                                                    {KEY_H, "h"}, 
                                                    {KEY_H, "H"}, 
                                                    {KEY_J, "j"}, 
                                                    {KEY_J, "J"}, 
                                                    {KEY_K, "k"}, 
                                                    {KEY_K, "K"}, 
                                                    {KEY_L, "l"}, 
                                                    {KEY_L, "L"}, 
                                                    {KEY_SEMICOLON, ";"}, 
                                                    {KEY_APOSTROPHE, "'"}, 
                                                    {KEY_GRAVE, "`"}, 
                                                    {KEY_LEFTSHIFT, "Left Shift"}, 
                                                    {KEY_BACKSLASH, "\\"}, 
                                                    {KEY_Z, "z"}, 
                                                    {KEY_Z, "Z"}, 
                                                    {KEY_X, "x"}, 
                                                    {KEY_X, "X"}, 
                                                    {KEY_C, "c"}, 
                                                    {KEY_C, "C"}, 
                                                    {KEY_V, "v"}, 
                                                    {KEY_V, "V"}, 
                                                    {KEY_B, "b"}, 
                                                    {KEY_B, "B"}, 
                                                    {KEY_N, "n"}, 
                                                    {KEY_N, "N"}, 
                                                    {KEY_M, "m"}, 
                                                    {KEY_M, "M"}, 
                                                    {KEY_COMMA, ","}, 
                                                    {KEY_DOT, "."}, 
                                                    {KEY_SLASH, "/"}, 
                                                    {KEY_RIGHTSHIFT, "Right Shift"}, 
                                                    {KEY_KPASTERISK, "*"}, 
                                                    {KEY_LEFTALT, "Left Alt"}, 
                                                    {KEY_SPACE, "Space"}, 
                                                    {KEY_CAPSLOCK, "Caps Lock"}, 
                                                    {KEY_F1, "F1"}, 
                                                    {KEY_F2, "F2"}, 
                                                    {KEY_F3, "F3"}, 
                                                    {KEY_F4, "F4"}, 
                                                    {KEY_F5, "F5"}, 
                                                    {KEY_F6, "F6"}, 
                                                    {KEY_F7, "F7"}, 
                                                    {KEY_F8, "F8"}, 
                                                    {KEY_F9, "F9"}, 
                                                    {KEY_F10, "F10"}, 
                                                    {KEY_NUMLOCK, "Num Lock"}, 
                                                    {KEY_SCROLLLOCK, "Scroll Lock"}, 
                                                    {KEY_KP7, "Numpad 7"}, 
                                                    {KEY_KP8, "Numpad 8"}, 
                                                    {KEY_KP9, "Numpad 9"}, 
                                                    {KEY_KPMINUS, "Numpad -"}, 
                                                    {KEY_KP4, "Numpad 4"}, 
                                                    {KEY_KP5, "Numpad 5"}, 
                                                    {KEY_KP6, "Numpad 6"}, 
                                                    {KEY_KPPLUS, "Numpad +"}, 
                                                    {KEY_KP1, "Numpad 1"}, 
                                                    {KEY_KP2, "Numpad 2"}, 
                                                    {KEY_KP3, "Numpad 3"}, 
                                                    {KEY_KP0, "Numpad 0"}, 
                                                    {KEY_KPDOT, "Numpad ."}, 
                                                    {KEY_F11, "F11"}, 
                                                    {KEY_F12, "F12"}, 
                                                    {KEY_KPENTER, "Numpad Enter"}, 
                                                    {KEY_RIGHTCTRL, "Right Ctrl"}, 
                                                    {KEY_KPSLASH, "Numpad /"}, 
                                                    {KEY_SYSRQ, "Print Screen"}, 
                                                    {KEY_RIGHTALT, "Right Alt"}, 
                                                    {KEY_HOME, "Home"}, 
                                                    {KEY_UP, "Arrow Up"}, 
                                                    {KEY_PAGEUP, "Page Up"}, 
                                                    {KEY_LEFT, "Arrow Left"}, 
                                                    {KEY_RIGHT, "Arrow Right"}, 
                                                    {KEY_END, "End"}, 
                                                    {KEY_DOWN, "Arrow Down"}, 
                                                    {KEY_PAGEDOWN, "Page Down"}, 
                                                    {KEY_INSERT, "Insert"}, 
                                                    {KEY_DELETE, "Delete"}, 
                                                    {KEY_PAUSE, "Pause/Break"}, 
                                                    {KEY_LEFTMETA, "Left Win"}, 
                                                    {KEY_LEFTMETA, "Left Function Key"}, 
                                                    {KEY_RIGHTMETA, "Right Win"}, 
                                                    {KEY_RIGHTMETA, "Right Function Key"}, 
                                                    {KEY_COMPOSE, "Compose"}
                                                };

class Key;
class KeyHandler;

class Key
{
public:
    //Кнопка была нажата
    void keyWasPressed();

    //Кнопка была отжата
    void keyWasReleased();

    //Функция добавления подписчика на события кнопки
    bool addSubscribe(KeyHandler* inputKeyHandler);

    //Функция удаления подписчика подписанного на события кнопки
    bool deleteSubscribe(KeyHandler* inputKeyHandler);

    //Функция установки кода клавиши
    void setKeyCode(int inputKeyCode);
    

private:
    std::unordered_map<KeyHandler*, std::list<KeyHandler*>::iterator> _keyHandlerHash;
    std::list<KeyHandler*> _keyHandlerList;
    bool _stateKey = false;
    int _keyCode = 0;
};

class KeyHandler
{
public:
    KeyHandler(std::vector<Key>* inputKeyVector);

    bool addKey(int inputKeyCode);

    bool removeKey(int inputKeyCode);

    void keyWasPressed();

    void keyWasReleased();

    void setDurationMs(int inputDuraitonMs);

    void setActionString(std::string inputActionString);

    void activation();


private:
    int _durationMs = 0;                    //Длительность ожидания нажатия клавиш в миллисекундах

    std::string _actionString = "nothing";  //Команда выполняемая при активации

    int _counterKeyPressed = 0;             //Счётчик нажатых клавиш

    std::chrono::time_point<std::chrono::high_resolution_clock> _startTime; //Время нажатия первой клавиши

    std::unordered_set<int> _keyCodeSet;    //Множество клавиш

    std::vector<Key>* _keyVector;           //Вектор клавиш
};


//Кнопка была нажата
void Key::keyWasPressed()
{
    if(!_stateKey)
    {
        for(const auto it : _keyHandlerList)
        {
            it->keyWasPressed();
        }

        //Запоминаем что кнопка нажата
        _stateKey = true;
    }
}


//Кнопка была отжата
void Key::keyWasReleased()
{
    if(_stateKey)
    {
        for(const auto it : _keyHandlerList)
        {
            it->keyWasReleased();
        }

        //Запоминаем что кнопка отжата
        _stateKey = false;
    }
}


//Функция добавления подписчика на события кнопки
bool Key::addSubscribe(KeyHandler* inputKeyHandler)
{
    //Ищем такого подписчика
    std::unordered_map<KeyHandler*, std::list<KeyHandler*>::iterator>::iterator findIterator = _keyHandlerHash.find(inputKeyHandler);

    //Если не нашли, то добавляем подписчика
    if(findIterator == _keyHandlerHash.end())
    {  
        //Добавляем в список KeyHandler
        std::list<KeyHandler*>::iterator insertIterator = _keyHandlerList.insert(_keyHandlerList.end(), inputKeyHandler);

        //Добавляем в хеш KeyHandler
        _keyHandlerHash.insert({inputKeyHandler, insertIterator});

        //Успешно добавили подписчика
        //Возвращаем true
        return true;
    }
    else
    {
        //Такой подписчик уже есть, добавления не произошло
        //Возвращаем false
        return false;
    }
}


//Функция удаления подписчика подписанного на события кнопки
bool Key::deleteSubscribe(KeyHandler* inputKeyHandler)
{
    //Ищем такого подписчика
    std::unordered_map<KeyHandler*, std::list<KeyHandler*>::iterator>::iterator findIterator = _keyHandlerHash.find(inputKeyHandler);

    //Если нашли, то удаляем подписчика
    if(findIterator != _keyHandlerHash.end())
    {  
        //Получаем итератор списка
        std::list<KeyHandler*>::iterator listIterator = findIterator->second;

        //Удаляем из списка итератор
        _keyHandlerList.erase(listIterator);

        //Удаляем из хеша итератор
        _keyHandlerHash.erase(findIterator);

        //inputKeyHandler

        //Успешно удалили подписчика
        //Возвращаем true
        return true;
    }
    else
    {
        //Такой подписчик нет, удаления не произошло
        //Возвращаем false
        return false;
    }
}

void Key::setKeyCode(int inputKeyCode)
{
    _keyCode = inputKeyCode;
}

KeyHandler::KeyHandler(std::vector<Key>* inputKeyVector)
{
    _keyVector = inputKeyVector;
    _startTime = std::chrono::high_resolution_clock::now();
}

bool KeyHandler::addKey(int inputKeyCode)
{
    //Ищем клавишу с inputKeyCode
    std::map<int, std::string>::iterator findIterator1 = keyCodesAndStringsMap.find(inputKeyCode);

    //Если такой клавиши нет
    if(findIterator1 == keyCodesAndStringsMap.end())
    {
        std::cerr << "\n\nFailed to add key, key not exist." << std::endl;

        //Возвращаем false, так как не удалось найти такую клавишу
        return false;
    }


    //Клавиша inputKeyCode существует
    //Узнаём есть ли уже такая клавиша в KeyHandler
    std::unordered_set<int>::iterator findIterator2 = _keyCodeSet.find(inputKeyCode);
    
    //Такая клавиша уже есть в KeyHandler
    if(findIterator2 != _keyCodeSet.end())
    {
        //Узнаём имя клавиши
        std::string keyName = findIterator1->second;

        std::cerr << "\n\nFailed to add key, observer already contains such a key. Key: " << keyName << "." << std::endl;

        //Возвращаем false, так как такая клавиша в KeyHandler уже есть
        return false;
    }


    //Клавиша inputKeyCode существует
    //В KeyHandler нет клавиши inputKeyCode
    //Получаем ссылку на клавишу, на которую хотим подписаться
    Key& refKey = (*_keyVector)[inputKeyCode];

    //Добавляем подписчика у клавиши
    if(refKey.addSubscribe(this))
    {
        //Добавляем клавишу во множество
        _keyCodeSet.insert(inputKeyCode).second;

        //Возвращаем true, так как удачно добавили клавишу
        return true;
    }
    else
    {
        std::cerr << "\n\nFailed to add key." << std::endl;

        //Возвращаем false, так как не удалось добавить клавишу
        return false;
    }
}

bool KeyHandler::removeKey(int inputKeyCode)
{
    //Ищем клавишу с inputKeyCode
    std::map<int, std::string>::iterator findIterator1 = keyCodesAndStringsMap.find(inputKeyCode);

    //Если такой клавиши нет
    if(findIterator1 == keyCodesAndStringsMap.end())
    {
        std::cerr << "\n\nFailed to remove key, key not exist." << std::endl;

        //Возвращаем false, так как не удалось найти такую клавишу
        return false;
    }


    //Клавиша inputKeyCode существует
    //Узнаём есть ли уже такая клавиша в KeyHandler
    std::unordered_set<int>::iterator findIterator2 = _keyCodeSet.find(inputKeyCode);
    
    //Такая клавиша уже есть в KeyHandler
    if(findIterator2 != _keyCodeSet.end())
    {
        //Узнаём имя клавиши
        std::string keyName = findIterator1->second;

        std::cerr << "\n\nFailed to remove key, observer not contains this key. Key: " << keyName << "." << std::endl;

        //Возвращаем false, так как такой клавиши в KeyHandler нет
        return false;
    }


    //Клавиша inputKeyCode существует
    //В KeyHandler есть клавиша inputKeyCode
    //Получаем ссылку на клавишу, от которой хотим отписаться
    Key& refKey = (*_keyVector)[inputKeyCode];

    //Удаляем подписчика у клавиши
    if(refKey.deleteSubscribe(this))
    {
        //Удаляем код клавиши из множества
        _keyCodeSet.erase(findIterator2);
    }
    else
    {
        std::cerr << "\n\nFailed to remove key." << std::endl;
    }

    //Возвращаем true, так как удачно удалили клавишу
    return true;
}

void KeyHandler::keyWasPressed()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> currentTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = currentTime - _startTime;

    int currentDuration_ms = round(duration.count()*1000);

    if(currentDuration_ms > _durationMs)
    {
        _counterKeyPressed = 0;
    }
    
    if(_counterKeyPressed == 0)
    {   
        _startTime = std::chrono::high_resolution_clock::now();
    }

    _counterKeyPressed++;

    if(_counterKeyPressed > _keyCodeSet.size())
    {
        _counterKeyPressed == _keyCodeSet.size();
    }

    if(_counterKeyPressed >= _keyCodeSet.size())
    {
        activation();
        _counterKeyPressed = 0;
    }
}

void KeyHandler::keyWasReleased()
{
    _counterKeyPressed--;
    
    if(_counterKeyPressed < 0)
    {
        _counterKeyPressed = 0;
    }
}

void KeyHandler::setDurationMs(int inputDuraitonMs)
{
    _durationMs = inputDuraitonMs;
}

void KeyHandler::setActionString(std::string inputActionString)
{
    _actionString = inputActionString;
}

void KeyHandler::activation()
{
    system(_actionString.c_str());
}


std::string execCommand(const std::string cmd, int& out_exitStatus)
{
    out_exitStatus = 0;

    auto pPipe = ::popen(cmd.c_str(), "r");

    if(pPipe == nullptr)
    {
        throw std::runtime_error("Cannot open pipe");
    }

    std::array<char, 256> buffer;

    std::string result;

    while(not std::feof(pPipe))
    {
        auto bytes = std::fread(buffer.data(), 1, buffer.size(), pPipe);
        result.append(buffer.data(), bytes);
    }

    auto rc = ::pclose(pPipe);

    if(WIFEXITED(rc))
    {
        out_exitStatus = WEXITSTATUS(rc);
    }

    return result;
}

bool deviceExists(const std::string& devicePath) 
{
    return (access(devicePath.c_str(), F_OK) != -1);
}

int main(int argc, char* argv[])
{    
    std::vector<Key> keyVector;
    
    keyVector.resize(KEY_COMPOSE + 1);

    for(int i = 0; i < keyVector.size(); i++)
    {
        keyVector[i].setKeyCode(i);
    }


    std::list<KeyHandler> keyHandlerList;


    // // Загрузка YAML файла
    // const char* filename = "CaptureKeyUtilityConfig.yaml";

    // //Открываем файл
    // FILE* file = fopen(filename, "r");
    // if(!file)
    // {
    //     std::cerr << "Failed to open file " << filename << std::endl;
    //     //Произошла ошибка при чтении события
    //     std::cerr << "Error: " << strerror(errno) << std::endl;
    //     return 1;
    // }

    // //Читаем содержимое файла в строку
    // fseek(file, 0, SEEK_END);
    // long fileSize = ftell(file);
    // fseek(file, 0, SEEK_SET);

    // std::string fileContent(fileSize, '\0');
    // fread(&fileContent[0], 1, fileSize, file);
    // fclose(file);

    // YAML::Node config = YAML::Load(fileContent);


    // Получаем путь к исполняемому файлу
    std::filesystem::path executablePath = std::filesystem::absolute(argv[0]);

    // Получаем директорию исполняемого файла
    std::filesystem::path executableDir = executablePath.parent_path();

    //Загружаем файл
    YAML::Node config = YAML::LoadFile(std::string(executableDir) + "/" + "CaptureKeyUtilityConfig.yaml");


    //Проверка наличия узла keyboard_shortcuts
    YAML::Node keyboard_shortcutsYAML = config["keyboard_shortcuts"];

    if(keyboard_shortcutsYAML)
    {
        for(const auto& shortcut : keyboard_shortcutsYAML)
        {
            //Узнаём существует ли поле duration
            YAML::Node durationYAML = shortcut["duration"];
            if(!durationYAML)
            {  
                std::cerr << "Not found duration in the YAML file.\n\n";
                continue;
            }

            //Проверяем тип
            if(durationYAML.Type() != YAML::NodeType::Scalar)
            {
                std::cerr << "Not found duration in the YAML file.\n\n";
                continue;
            }
            
            //Получаем значение из поля keyboard_shortcuts
            int duration = durationYAML.as<int>();
            

            //Узнаём существует ли поле action_string
            YAML::Node action_stringYAML = shortcut["action_string"];

            if(!action_stringYAML)
            {  
                std::cerr << "Not found action_string in the YAML file.\n\n";
                continue;
            }

            //Проверяем тип
            if(action_stringYAML.Type() != YAML::NodeType::Scalar)
            {
                std::cerr << "Not found action_string in the YAML file.\n\n";
                continue;
            }

            //Получаем значение из поля action_string
            std::string action_string = action_stringYAML.as<std::string>();


            //Узнаём существует ли поле keys
            YAML::Node keysYAML = shortcut["keys"];

            if(!keysYAML)
            {  
                std::cerr << "Not found keys in the YAML file.\n\n";
                continue;
            }

            //Получаем значение из поля keys
            std::vector<std::string> keysStrings;

            //Узнаём является ли поле keys последовательностью
            switch(keysYAML.Type())
            {
                case YAML::NodeType::Sequence:
                {
                    //Получаем значения из поля keys
                    keysStrings = keysYAML.as<std::vector<std::string>>();
                    break;
                }
                case YAML::NodeType::Scalar:
                {
                    //Получаем значение из поля keys
                    std::string keyString = keysYAML.as<std::string>();
                    keysStrings.push_back(keyString);
                    break;
                }
                default:
                    std::cerr << "Not found keys in the YAML file.\n\n";
                    continue;
                    break;
            }


            //Проверяем не пустое ли это поле
            if(keysStrings.empty())
            {
                std::cerr << "Keys is empty.\n\n";
                continue;
            }


            std::vector<int> keysCodes;
            std::vector<int> indexErrorVector;


            //Вывод данных
            std::cout << "Duration: " << duration << "\n";
            std::cout << "Action String: " << action_string << "\n";
            std::cout << "Keys: ";
            
            
            //Преобразуем строки в коды
            for(int i = 0; i < keysStrings.size(); i++)
            {
                //Ищем соответствующий строке код
                std::map<std::string, int>::iterator findIterator = stringsAndKeyCodesMap.find(keysStrings[i]);

                //Если не нашли, то добавляем в вектор ошибок индекс кнопки
                if(findIterator == stringsAndKeyCodesMap.end())
                {
                    indexErrorVector.push_back(i);
                }
                else
                {
                    //Нашли, выводим на экран
                    if(i > 0)
                    {
                        std::cout << ", ";
                    }

                    std::cout << keysStrings[i];

                    //Добавляем код клавиши в векторо кодов клавиш
                    keysCodes.push_back(findIterator->second);
                }
            }
            
            //Если ниодного кода клавиши не было добавлено
            if(keysCodes.empty())
            {
                std::cerr << "Keys is empty.\n\n";
            }
            else
            {
                keyHandlerList.push_back(KeyHandler(&keyVector));
                KeyHandler& refKeyHandler = keyHandlerList.back();
                refKeyHandler.setDurationMs(duration);
                refKeyHandler.setActionString(action_string);

                for(const auto& key : keysCodes)
                {
                    //Добавляем клавишу
                    bool res = refKeyHandler.addKey(key);

                    // //Если не вышло добавить клавишу
                    // if(!res)
                    // {
                    //     //Удаляем ранее добавленные клавиши
                    //     for(const auto& key : keysCodes)
                    //     {
                    //         refKeyHandler.removeKey(key);
                    //     }

                    //     keyHandlerList.pop_back();

                    //     continue;
                    // }
                }
            }

            for(const auto& index : indexErrorVector)
            {
                //Если не нашли, то пропускаем
                std::cerr << "\n\nFailed to add key, key not exist, key: " << keysStrings[index] << "\n\n";
            }

            std::cout << "\n\n";
        }
    }
    else
    {
        std::cerr << "Not found keyboard_shortcuts in the YAML file.\n" << std::endl;
    }


    int fd;
    struct libevdev *dev = nullptr;
    int rc;


    while(true)
    {
        std::vector<std::string> deviceVector;

        const std::string inputDir = "/dev/input";

        for(const auto& entry : std::filesystem::directory_iterator(inputDir))
        {
            if(entry.is_character_file())
            {
                std::string filename = entry.path().filename().string();

                if(filename.compare(0, 5, "event") == 0)
                {
                    deviceVector.push_back(entry.path());
                }
            }
        }


        bool deviceFinded = false;
       
        for(const auto& currentDevice : deviceVector)
        {
            fd = open(currentDevice.c_str(), O_RDONLY);

            if(fd < 0)
            {
                std::cerr << "Failed open device, error:" << strerror(-fd) << std::endl;
            }

            rc = libevdev_new_from_fd(fd, &dev);
            if(rc < 0)
            {
                std::cerr << "Failed initialization library libevdev, error: " << strerror(-rc) << std::endl;
                close(fd);
            }


            // Проверяем типы событий
            if(libevdev_has_event_type(dev, EV_ABS))
            {
                close(fd);
                continue;
            }
            if(libevdev_has_event_type(dev, EV_REL))
            {
                close(fd);
                continue;
            }
            if(libevdev_has_event_type(dev, EV_KEY))
            {
                deviceFinded = true;
                break;
            }
        }
        
        if(!deviceFinded)
        {
            sleep(1);
            continue;
        }


        std::cout << "Device: " << libevdev_get_name(dev) << std::endl;
        
        while(true)
        {
            struct input_event ev;

            int rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);

            if(rc == LIBEVDEV_READ_STATUS_SUCCESS)
            {
                if(ev.type == EV_KEY)
                {
                    switch(ev.value)
                    {
                        //Клавиша была отжата
                        case 0:
                        {
                            keyVector[ev.code].keyWasReleased();
                            break;
                        }
                        //Клавиша была нажата
                        case 1:
                        {
                            keyVector[ev.code].keyWasPressed();
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
            else if(rc == LIBEVDEV_READ_STATUS_SYNC)
            {
                continue;
            }
            else
            {  
                //Произошла ошибка при чтении события
                std::cerr << "Failed read event, error: " << strerror(-rc) << std::endl;

                if(-rc == 19)
                {
                    close(fd);
                    break;
                }
            }
        }
    }

    libevdev_free(dev);
    close(fd);
    return 0;
}
