# Утилита для биндинга горячих клавиш в Linux
Утилиту предназначена для связки горячей клавиши и любой команды в терминале.

Например, при нажатии клавиш `Left Ctrl` + `Left Shift` + `F1` выводить к консоль текст `pressed Left Ctrl + Left Shift + F1`, выполнив команду:

```shell
echo "pressed Left Ctrl + Left Shift + F1"
```

Связку можно задавать вручную при помощи yaml-файла.

## Зависимости
* Для сборки используется CMake
* Для парсинга yaml используется библиотека [`yaml-cpp`](https://github.com/jbeder/yaml-cpp). В проекте есть header-файлы и собранная статическая версия собранная для архитектуры `aarch64`.
* Для работы с клавиатурой используется библиотека [`libevdev`](https://www.freedesktop.org/software/libevdev/doc/latest/).

Установка в Debian/Ubuntu:
```shell
sudo apt install libevdev-dev
```

Установка в Fedora:
```shell
sudo dnf install libevdev-devel
```

## Использование собранной утилиты
Для конфигурации связок горячих клавиш и команд используется файл `CaptureKeyUtilityConfig.yaml`. Пример его заполнения:
```yaml
keyboard_shortcuts:
  # Первый бинд
  - duration: 400
    action_string: "echo "pressed Left Ctrl + Left Shift + F1""
    keys:
      - "Left Ctrl"
      - "Left Shift"
      - "F1"

  # Второй бинд
  - duration: 400
    action_string: "echo "pressed Left Ctrl + Left Shift + F2""
    keys:
      - "Left Ctrl"
      - "Left Shift"
      - "F2"
```
Файл считывается при запуске утилиты. 

## TODO
- [ ] Подключить `yaml-cpp` в качестве исходников для сборки на разных платформах.