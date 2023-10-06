#include <functional>
#include <string>

template<typename T>
class trigger
{
public:

    T value;

    // Constructors

    trigger() {}

    template<typename U>
    trigger(const U& operand) {
        value = operand;
    }

    // Overloading the cast operator

    template <typename U>
    operator U() const {
        return this->value;
    }

    operator T() const {
        return this->value;
    }

    // Overloading operators with type

    // Operator <<
    friend std::ostream& operator<<(std::ostream& result, const trigger& operand) {
        result << operand.value;
        return result;
    }

    // Operator =
    template<typename U>
    trigger& operator = (const U& operand) {
        this->value = operand;
        _call();
        return *this;
    }

    // Operator a++
    trigger operator++(const int) {
        trigger temp(*this);
        ++(*this);
        return temp;
    }

    // Operator ++a
    trigger& operator ++ () {
        value++;
        _call();
        return *this;
    }

    // Operator a--
    trigger operator--(const int) {
        trigger temp(*this);
        --(*this);
        return temp;
    }

    // Operator --a
    trigger& operator -- () {
        value--;
        _call();
        return *this;
    }

    // Operator +=
    template<typename U>
    trigger& operator += (const U operand) {
        value += operand;
        _call();
        return *this;
    }

    // Operator -=
    template<typename U>
    trigger& operator -= (const U operand) {
        value -= operand;
        _call();
        return *this;
    }

    // Operator *=
    template<typename U>
    trigger& operator *= (const U operand) {
        value *= operand;
        _call();
        return *this;
    }

    // Operator /=
    template<typename U>
    trigger& operator /= (const U operand) {
        value /= operand;
        _call();
        return *this;
    }

    // Operator %=
    template<typename U>
    trigger& operator %= (const U operand) {
        value %= operand;
        _call();
        return *this;
    }

    // Class Methods

    void call() {
        _func = nullptr;
    }

    template<typename Func, typename... Args>
    void call(Func func, Args... args) {
        this->_func = std::bind(func, args...);
    }

private:
    std::function<void()> _func = nullptr;
    std::function<void()> _call = [this]() {
        if (this->_func != nullptr)
            this->_func();
    };
};