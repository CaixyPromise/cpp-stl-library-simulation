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
        char* _str;       // �洢�ַ������ݵ��ַ�����
        size_t _capacity; // �ַ�����ķ�������
        size_t _size;     // �ַ����ĳ��ȣ��ַ�������
        static const size_t npos = -1;

    public:
        typedef char* iterator;
        typedef const char* const_iterator;

        // ���캯��������һ���ַ������󲢳�ʼ��Ϊָ����C����ַ���
        string(const char* str = "")
            : _capacity(strlen(str) + 1)
        {
            _str = new char[_capacity];
            _size = strlen(str);
            strcpy(_str, str);
        }

        // �������캯�����������е��ַ������󴴽��µĶ���
        string(const string& s)
            : _size(0)
            , _capacity(0)
            , _str(nullptr)
        {
            string tmp(s.c_str());
            swap(tmp);
        }

        // ��ֵ��������أ���һ���ַ�����������ݸ�ֵ����һ������
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

        // �����������ͷ��ַ�������ռ�õ���Դ
        ~string()
        {
            delete[] _str;
            _size = 0;
            _capacity = 0;
        }

        // �������Ŀ�ʼλ��
        iterator begin()
        {
            return _str;
        }

        // �������Ľ���λ�ã�ĩβԪ�ص���һ��λ�ã�
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

        // ���ַ���ĩβ���һ���ַ�
        void push_back(char c)
        {
            insert(_size, c);
        }

        // ��һ���ַ�׷�ӵ��ַ���ĩβ���������µ��ַ�������
        string& operator+=(char c)
        {
            return insert(_size, c);
        }

        // ���ַ���ĩβ׷��һ��C����ַ���
        void append(const char* str)
        {
            insert(_size, str);
        }

        // ��һ��C����ַ���׷�ӵ��ַ���ĩβ���������µ��ַ�������
        string& operator+=(const char* str)
        {
            return insert(_size, str);
        }

        // ����ַ������ͷ��ڴ�
        void clear()
        {
            _str[0] = '\0';
            _size = 0;
        }

        // ���������ַ������������
        void swap(string& s)
        {
            std::swap(_str, s._str);
            std::swap(_size, s._size);
            std::swap(_capacity, s._capacity);
        }

        // ������ null ��β�� C ����ַ���
        const char* c_str() const
        {
            return _str;
        }

        // �����ַ����ĳ��ȣ��ַ�������
        size_t size() const
        {
            return _size;
        }

        // �����ַ�����������������ڴ��С��
        size_t capacity() const
        {
            return _capacity;
        }

        // �����ַ����Ƿ�Ϊ��
        bool empty() const
        {
            return _size == 0;
        }

        // �����ַ����Ĵ�С������µĴ�С���ڵ�ǰ��С�������ָ���ַ�
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

        // ����������� n ���ַ����ڴ�
        void reserve(size_t n)
        {
            //n С�ڵ�ǰ _capacity������Ҫ���·����ڴ棬ֱ������ַ��������ؼ��ɡ�
            if (n > _capacity)
            {
                char* tmp = new char[_capacity + n + 1];
                strcpy(tmp, _str);
                delete[] _str;
                _str = tmp;
                _capacity += n;
            }
        }

        // �����ַ�����ָ������λ�õ��ַ����ɶ�д��
        char& operator[](size_t index)
        {
            assert(index >= _size);
            return _str[index];
        }

        // �����ַ�����ָ������λ�õ��ַ���ֻ����
        const char& operator[](size_t index) const
        {
            assert(index >= _size);
            return _str[index];
        }

        // �Ƚ����������
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

        // ���ַ����в���ָ���ַ������ص�һ�γ��ֵ�λ��
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

        // ���ַ����в���ָ���Ӵ������ص�һ�γ��ֵ�λ��
        size_t find(const char* s, size_t pos = 0) const
        {
            if (pos < 0)
            {
                return npos;
            }
            // �����ַ���
            const char* result = strstr(_str, s);
            if (result != nullptr)
            {
                return result - _str;
            }
            else {
                return npos;
            }
        }

        // ��ָ��λ�ò����ַ������ز����ַ���λ��
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

        // ��ָ��λ�ò����ַ��������ز����ַ�����λ��
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
        // ɾ��ָ��λ�ÿ�ʼ�� len ���ַ�������ɾ�����λ��
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