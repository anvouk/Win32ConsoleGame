#include <fmt/format.h>
#include <console-framework/test.h>

int main(int argc, char* argv[])
{
    fmt::print("res is: {}", test());
    return 0;
}
