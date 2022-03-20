#pragma once

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>


template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& out, const std::pair<Key, Value>& container)
{
    using namespace std;
    out << container.first << ": " << container.second;
    return out;
}

template <typename Term>
std::ostream& Print(std::ostream& out, Term& container)
{
    using namespace std;
    bool first = false;
    for (const auto& element : container) 
    {
        if (!first) 
        {
            first = true;
            out << element;
        }
        else {
            out << ", "s << element;
        }
    }
    return out;
}

template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& out, const std::map<Key, Value>& container)
{
    using namespace std;
    out << "{"s;
    Print(out, container);
    out << "}"s;
    return out;
}


template <typename Term>
std::ostream& operator<<(std::ostream& out, const std::vector<Term>& container)
{
    using namespace std;
    out << "["s;
    Print(out, container);
    out << "]"s;
    return out;
}

template <typename Term>
std::ostream& operator<<(std::ostream& out, const std::set<Term>& container)
{
    using namespace std;
    out << "{"s;
    Print(out, container);
    out << "}"s;
    return out;
}



template <typename T, typename U>
void AssertEqualImpl(const T& t, const U& u, const std::string& t_str, const std::string& u_str, 
    const std::string& file, const std::string& func, unsigned line, const std::string& hint
)
{
    using namespace std;
    if (t != u) 
    {
        cerr << boolalpha;
        cerr << file << "("s << line << "): "s << func << ": "s;
        cerr << "ASSERT_EQUAL("s << t_str << ", "s << u_str << ") failed: "s;
        cerr << t << " != "s << u << "."s;
        if (!hint.empty()) {
            cerr << " Hint: "s << hint;
        }
        cerr << endl;
        abort();
    }
}

#define ASSERT_EQUAL(a, b) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, ""s)

#define ASSERT_EQUAL_HINT(a, b, hint) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, (hint))

void AssertImpl(bool value, const std::string& expr_str, 
    const std::string& file, const std::string& func, unsigned line, const std::string& hint
)
{
    using namespace std;
    if (!value) 
    {
        cerr << file << "("s << line << "): "s << func << ": "s;
        cerr << "ASSERT("s << expr_str << ") failed."s;
        if (!hint.empty()) {
            cerr << " Hint: "s << hint;
        }
        cerr << endl;
        abort();
    }
}

#define ASSERT(expr) AssertImpl(!!(expr), #expr, __FILE__, __FUNCTION__, __LINE__, ""s)

#define ASSERT_HINT(expr, hint) AssertImpl(!!(expr), #expr, __FILE__, __FUNCTION__, __LINE__, (hint))


#define RUN_TEST(func) func(); std::cerr << #func << " OK" << std::endl

/*
/////////////////////////////////////////////////////////////
// EXAMPLE OF IMPLEMENTATION USE
/////////////////////////////////////////////////////////////
void Test1()
{
    ASSERT(4 == 4);
    ASSERT_HINT(5 == 5, "Some hint");
    ASSERT_EQUAL(4, 4);
    ASSERT_EQUAL_HINT(5, 5, "Some hint");
}

void TestLauncher()
{
    RUN_TEST(Test1);
    RUN_TEST(Test1);
    RUN_TEST(Test1);
}

int main()
{
    TestLauncher();
}
*/

