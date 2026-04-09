#include "math_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

namespace calc_easy {
struct CalculatorData {
    int first_num;
    int second_num;
    char operator_;
    int result;
    int status;
};

void Parser(int argc, char *argv[], CalculatorData &data);
void Checker(CalculatorData &data);
void Calculator(CalculatorData &data);
void Printer(const CalculatorData &data);
void Runner(int argc, char *argv[]);

} // namespace calc_easy

int main(int argc, char *argv[]) {
    calc_easy::Runner(argc, argv);
    return 0;
}

namespace calc_easy {
void Runner(int argc, char *argv[]) {
    CalculatorData data = {0, 0, 0, 0, 0};
    Parser(argc, argv, data);
    Checker(data);
    if (data.status == 0) {
        Calculator(data);
        Printer(data);
    }
}

void Parser(int argc, char *argv[], CalculatorData &data) {
    int opt;
    optind = 1;
    const int kbase = 10;
    while ((opt = getopt(argc, argv, "a:b:o:h")) != -1) {
        switch (opt) {
        case 'a':
            data.first_num = (int)strtol(optarg, NULL, kbase);
            break;
        case 'b':
            data.second_num = (int)strtol(optarg, NULL, kbase);
            break;
        case 'o':
            data.operator_ = optarg[0];
            break;
        case 'h':
            printf("Usage: calculator -a [num1] -b [num2] -o [operator]\n");
            printf("Operators: + (add), - (sub), * (mul), / (div), ^ (pow), ! "
                   "(fact)\n");
            printf("Example: ./calculator -a 5 -b 2 -o ^\n");
            data.status = 1;
            break;
        default:
            data.status = 1;
            break;
        }
    }
}

void Checker(CalculatorData &data) {
    if (data.status != 0) {
        return;
    }
    bool valid_op = false;
    char ops[] = {'+', '-', '*', '/', '^', '!'};
    int ops_count = sizeof(ops) / sizeof(ops[0]);
    for (int i = 0; i < ops_count; ++i) {
        if (data.operator_ == ops[i]) {
            valid_op = true;
            break;
        }
    }

    if (!valid_op) {
        printf("Error: Invalid or missing operator '%c'.\n", data.operator_);
        data.status = 1;
        return;
    }
    if (data.operator_ == '/' && data.second_num == 0) {
        printf("Error: Division by zero is not allowed.\n");
        data.status = 1;
        return;
    }
    if (data.operator_ == '!' && data.first_num < 0) {
        printf("Error: Factorial of a negative number is undefined.\n");
        data.status = 1;
        return;
    }
    if (data.operator_ == '^' && data.second_num < 0) {
        printf("Error: Negative exponent is not supported for integers.\n");
        data.status = 1;
        return;
    }
}

void Calculator(CalculatorData &data) {
    if (data.status != 0) {
        return;
    }

    bool overflow = false;
    // NOLINTNEXTLINE(bugprone-branch-clone)
    switch (data.operator_) {
    case '+':
        data.result =
            math_utils::Add(data.first_num, data.second_num, overflow);
        break;
    case '-':
        data.result =
            math_utils::Sub(data.first_num, data.second_num, overflow);
        break;
    case '*':
        data.result =
            math_utils::Mul(data.first_num, data.second_num, overflow);
        break;
    case '/':
        data.result =
            math_utils::Div(data.first_num, data.second_num, overflow);
        break;
    case '^':
        data.result =
            math_utils::Pow(data.first_num, data.second_num, overflow);
        break;
    case '!':
        data.result = math_utils::Fact(data.first_num, overflow);
        break;
    default:
        overflow = true;
        break;
    }

    if (overflow) {
        printf("Error: Arithmetic overflow occurred!\n");
        data.status = 1;
    }
}

void Printer(const CalculatorData &data) {

    if (data.status != 0) {
        return;
    }

    if (data.operator_ == '!') {

        printf("%d%c = %d\n", data.first_num, data.operator_, data.result);
    } else {
        printf("%d %c %d = %d\n", data.first_num, data.operator_,
               data.second_num, data.result);
    }
}

} // namespace calc_easy
