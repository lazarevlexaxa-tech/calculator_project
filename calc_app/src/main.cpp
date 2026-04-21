#include "Runner.hpp"

int main(int argc, char **argv) {
    try {
        Runner app;
        app.run(argc, argv);
        return 0;
    } catch (...) {
        return 1;
    }
}
