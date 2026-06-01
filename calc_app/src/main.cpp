#include "Runner.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    try {
        // Всё тело функции внутри try
        Runner app;
        app.run(argc, argv);
    } catch (const std::exception &e) {
        // Если что-то пошло не так на уровне запуска
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        // На случай совсем неведомых ошибок
        std::cerr << "Unknown fatal error!" << std::endl;
        return 1;
    }

    return 0;
}
