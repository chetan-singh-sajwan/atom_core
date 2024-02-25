import atom.core;

using namespace atom;

auto print(string_view str)
{
    std::string_view std_str(str.data().as_unsafe<char>().to_unwrapped(), str.count().to_unwrapped());
    std::cout << std_str;
}

auto println(string_view str)
{
    print(str);
    std::cout << std::endl;
}

auto main(int argc, char** args) -> int
{
    return 0;
}
