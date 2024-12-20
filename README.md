# URL Downloader

## Описание
Консольное приложение для параллельной загрузки файлов по URL.

В CMakeLists.txt помечены строчки, для изменения пути до библиотек.

## Требования
- C++11/14/17
- CMake 3.10+
- Библиотеки:
  - [cpr](https://github.com/libcpr/cpr)
  - [spdlog](https://github.com/gabime/spdlog)
  - [fmt](https://github.com/fmtlib/fmt)
  - [googletest](https://github.com/google/googletest)

## Сборка
cd build
cmake ..
make

## Тесты
cd build
ctest

Чтобы посмотреть полный вывод выполнения тестов:
./UrlDownloaderTests