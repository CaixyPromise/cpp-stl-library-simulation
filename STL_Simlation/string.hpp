#ifndef STRING_HPP
#define STRING_HPP

#include "common.hpp"


namespace syu_str
{
    class string
    {
        friend ostream& operator<<(ostream& _cout, const syu_str::string& s);
        friend istream& operator>>(istream& _cin, syu_str::string& s);
    private:
        char* _str;       // 存储字符串内容的字符数组
        size_t _capacity; // 字符数组的分配容量
        size_t _size;     // 字符串的长度（字符个数）
        static const size_t npos = -1;

    public:
        typedef char* iterator;
        typedef const char* const_iterator;

        // 构造函数，创建一个字符串对象并初始化为指定的C风格字符串
        string(const char* str = "")
            : _capacity(strlen(str) + 1)
        {
            _str = new char[_capacity];
            _size = strlen(str);
            strcpy(_str, str);
        }

        // 拷贝构造函数，根据已有的字符串对象创建新的对象
        string(const string& s)
            : _size(0)
            , _capacity(0)
            , _str(nullptr)
        {
            string tmp(s.c_str());
            swap(tmp);
        }

        // 赋值运算符重载，将一个字符串对象的内容赋值给另一个对象
        string& operator=(const string& s)
        {
            if (*this != s)
            {
                char* tmp = new char[s._capacity];
                _size = s._size;
                _capacity = s._capacity;
                strcpy(tmp, s._str);
                delete[] _str;
                _str = tmp;
            }
            return *this;
        }

        // 析构函数，释放字符串对象占用的资源
        ~string()
        {
            delete[] _str;
            _size = 0;
            _capacity = 0;
        }

        // 迭代器的开始位置
        iterator begin()
        {
            return _str;
        }

        // 迭代器的结束位置（末尾元素的下一个位置）
        iterator end()
        {
            return _str + _size;
        }

        const_iterator const_begin() const
        {
            return _str;
        }

        const_iterator const_end() const
        {
            return _str + _size;
        }

        // 在字符串末尾添加一个字符
        void push_back(char c)
        {
            insert(_size, c);
        }

        // 将一个字符追加到字符串末尾，并返回新的字符串对象
        string& operator+=(char c)
        {
            return insert(_size, c);
        }

        // 在字符串末尾追加一个C风格字符串
        void append(const char* str)
        {
            insert(_size, str);
        }

        // 将一个C风格字符串追加到字符串末尾，并返回新的字符串对象
        string& operator+=(const char* str)
        {
            return insert(_size, str);
        }

        // 清空字符串，释放内存
        void clear()
        {
            _str[0] = '\0';
            _size = 0;
        }

        // 交换两个字符串对象的内容
        void swap(string& s)
        {
            std::swap(_str, s._str);
            std::swap(_size, s._size);
            std::swap(_capacity, s._capacity);
        }

        // 返回以 null 结尾的 C 风格字符串
        const char* c_str() const
        {
            return _str;
        }

        // 返回字符串的长度（字符个数）
        size_t size() const
        {
            return _size;
        }

        // 返回字符串的容量（分配的内存大小）
        size_t capacity() const
        {
            return _capacity;
        }

        // 返回字符串是否为空
        bool empty() const
        {
            return _size == 0;
        }

        // 调整字符串的大小，如果新的大小大于当前大小，则填充指定字符
        void resize(size_t n, char c = '\0')
        {
            if (n <= _size)
            {
                _str[n] = '\0';
                _size = n;
            }
            else {
                if (n + _size > _capacity)
                {
                    reserve(n);
                }
                memset(_str + _size, c, n - _size);
                _size += n;
                _str[_size] = '\0';
            }
        }

        // 请求分配至少 n 个字符的内存
        void reserve(size_t n)
        {
            //n 小于当前 _capacity，不需要重新分配内存，直接填充字符串并返回即可。
            if (n > _capacity)
            {
                char* tmp = new char[_capacity + n + 1];
                strcpy(tmp, _str);
                delete[] _str;
                _str = tmp;
                _capacity += n;
            }
        }

        // 访问字符串中指定索引位置的字符（可读写）
        char& operator[](size_t index)
        {
            assert(index >= _size);
            return _str[index];
        }

        // 访问字符串中指定索引位置的字符（只读）
        const char& operator[](size_t index) const
        {
            assert(index >= _size);
            return _str[index];
        }

        // 比较运算符重载
        bool operator<(const string& s) const
        {
            return strcmp(_str, s._str) < 0;
        }

        bool operator<=(const string& s) const
        {
            return strcmp(_str, s._str) <= 0;
        }

        bool operator>(const string& s) const
        {
            return strcmp(_str, s._str) > 0;
        }

        bool operator>=(const string& s) const
        {
            return strcmp(_str, s._str) >= 0;
        }

        bool operator==(const string& s) const
        {
            return strcmp(s._str, _str) == 0;
        }
        bool operator!=(const string& s) const
        {
            return strcmp(s._str, _str) != 0;
        }

        // 在字符串中查找指定字符，返回第一次出现的位置
        size_t find(char c, size_t pos = 0) const
        {
            if (pos < 0)
            {
                return npos;
            }

            for (size_t i = pos; i < _size; i++)
            {
                if (_str[i] == c)
                {
                    return i;
                }
            }
            return npos;
        }

        // 在字符串中查找指定子串，返回第一次出现的位置
        size_t find(const char* s, size_t pos = 0) const
        {
            if (pos < 0)
            {
                return npos;
            }
            // 查找字符串
            const char* result = strstr(_str, s);
            if (result != nullptr)
            {
                return result - _str;
            }
            else {
                return npos;
            }
        }

        // 在指定位置插入字符，返回插入字符的位置
        string& insert(size_t pos, char c)
        {
            assert(pos <= _size);
            if (_size == _capacity)
            {
                reserve(_capacity == 0 ? 4 : _capacity * 4);
            }

            size_t end = _size + 1;
            while (pos < end)
            {
                _str[end] = _str[end - 1];
                end--;
            }
            _size++;
            _str[pos] = c;
            return *this;
        }

        // 在指定位置插入字符串，返回插入字符串的位置
        string& insert(size_t pos, const char* str)
        {
            assert(pos <= _size && str != nullptr);
            size_t length = strlen(str);
            if (_size + length > _capacity)
            {
                reserve(_capacity == 0 ? 4 : _capacity * 4);
            }

            size_t end = _size + length;
            while (end > pos + length)
            {
                _str[end] = _str[end - length];
                end--;
            }

            strncpy(_str + pos, str, length);
            _size += length;
            _str[_size] = '\0';
            return *this;
        }
        // 删除指定位置开始的 len 个字符，返回删除后的位置
        string& erase(size_t pos, size_t len = npos)
        {
            assert(pos < _size);

            if (len == npos || pos + len >= _size)
            {
                _str[pos] = '\0';
                _size = pos;
            }
            else {
                strcpy(_str + pos, _str + pos + len);
                _size -= len;
            }
            return *this;
        }


    };
    ostream& operator<<(ostream& _cout, const string& s)
    {
        for (size_t i = 0; i < s.size(); i++)
        {
            _cout << s[i];
        }
        return _cout;
    }

    istream& operator>>(istream& _cin, string& s)
    {
        s.clear();
        char ch = _cin.get();
        while (ch != ' ' && ch != '\n')
        {
            s += ch;
            ch = _cin.get();
        }
        return _cin;
    }
};


namespace Test_string
{
    using namespace syu_str;

    void test_constructors() 
    {
        syu_str::string s1("Hello");
        syu_str::string s2(s1);

        assert(s1 == s2);
        assert(s1.size() == s2.size());
        assert(s1.capacity() == s2.capacity());
        assert(strcmp(s1.c_str(), s2.c_str()) == 0);
    }

    void test_assignment_operator() 
    {
        syu_str::string s1("Hello");
        syu_str::string s2;
        s2 = s1;

        assert(s1 == s2);
        assert(s1.size() == s2.size());
        assert(s1.capacity() == s2.capacity());
        assert(strcmp(s1.c_str(), s2.c_str()) == 0);
    }

    void test_methods() 
    {
        syu_str::string s("Hello, World!");

        assert(s.size() == 13);
        assert(s.capacity() >= 13);
        assert(strcmp(s.c_str(), "Hello, World!") == 0);
    }

    void test_equality_operator() 
    {
        syu_str::string s1("Hello");
        syu_str::string s2("Hello");
        syu_str::string s3("World");

        assert(s1 == s2);
        assert(!(s1 == s3));
    }

    void callTestFunction()
    {
        test_constructors();
        output_log("string", "test_assignment_operator passed!");

        test_assignment_operator();
        output_log("string", "Test: test_assignment_operator passed!");

        test_methods();
        output_log("string", "test_methods passed!");

        test_equality_operator();
        output_log("string", "test_equality_operator passed!");

        output_log("string", "All string tests passed!");
    }
}

#endif // STRING_HPP