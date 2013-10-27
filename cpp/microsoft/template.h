#include <iostream>

template <typename T>
class Exemple
{
public :

    Exemple(const T& Val = T());

    template <typename U>
    Exemple(const Exemple<U>& Copy);

    const T& Get() const;

    template <typename T2>
    friend std::ostream& operator <<(std::ostream& Stream, const Exemple<T2>& Ex);

private :

    T Value;
};

template <typename T>
Exemple<T>::Exemple(const T& Val) :
Value(Val)
{

}

template <typename T>
template <typename U>
Exemple<T>::Exemple(const Exemple<U>& Copy) :
Value(static_cast<T>(Copy.Get()))
{
    // Attention, ceci n'est pas le constructeur par copie !
}

template <typename T>
const T& Exemple<T>::Get() const
{
    return Value;
}

template <typename T>
std::ostream& operator <<(std::ostream& Stream, const Exemple<T>& Ex)
{
    return Stream << Ex.Value;
}


