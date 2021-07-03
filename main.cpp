#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

// ----- Task 1
template<class T>
class Pair1
{
private:
    T x;
    T y;
public:
    Pair1(T X, T Y): x(X),y(Y) {};
    ~Pair1() {}
    T first() const { return x;}
    T second() const { return y;}
};

// ----- Task 2
template<class P, class O>
class Pair
{
private:
    P x;
    O y;
public:
    Pair(P X, O Y): x(X),y(Y) {};
    ~Pair() {}
    P first() const { return x;}
    O second() const { return y;}
};

// ----- Task 3
template <class O>
class StringValuePair: public Pair<std::string, O>
{
public:
    StringValuePair(std::string st, O Y): Pair<std::string, O>(st,Y) {};
};

// ----- Task 4

class Card {
public:
  enum znashen {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
           JACK, QUEEN, KING};
  enum mast {CLUBS, DIAMONDS, HEARTS, SPADES};

  Card(znashen r, mast s, bool ifUp): m_Znashen(r), m_Mast(s), m_IsFaceUp(ifUp)
  {}

  // возвращает значение карты, пока можно считать, что туз = 1
  int GetValue() const
  {
   int value = 0;
   if (m_IsFaceUp)
    {
      value = m_Znashen;
      if (value > 10) value = 10;
    }
   return value;
  };

  // переворачивает карту
  void Flip()
  {
     m_IsFaceUp = !(m_IsFaceUp);
  };

private:
  znashen m_Znashen;
  mast m_Mast;
  bool m_IsFaceUp;
};

class Hand
{

protected:
  vector <Card*> m_Cards;

public:
  Hand()
  {
   m_Cards.reserve(7);
  }
         ;

  // добавляет в коллекцию карт новую карту
  void Add(Card* pCard)
  {
    m_Cards.push_back(pCard);
  }

  // очищает руку от карт
  void Clear()
  {
    //iterate through vector, freeing all memory on the heap
    vector <Card*>::iterator iter = m_Cards.begin();
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
      delete *iter;
      *iter = 0; //get rid of dangling pointer - null pointer
    }
    m_Cards.clear();
  }

  // возвращает сумму очков карт руки, туз принимает значения 1 или 11
  int GetTotal() const
{

  //если нет карт, возвращает 0
  if (m_Cards.empty()) return 0;

  // если первая карта 0, то карты закрыта, возвращает 0
  if (m_Cards[0]->GetValue() == 0) return 0;

  // сложение значения карт, относимся к каждому тузу как к 1
  int total = 0;
  vector<Card*>::const_iterator iter;
  for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
  total += (*iter)->GetValue();

  // определяем, есть ли в руке туз
  bool containsAce = false;
  for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
  if ((*iter)->GetValue() == Card::ACE)
    containsAce = true;

  // если в руке есть туз, а сумма достаточно низкая, то туз считается 11
  if (containsAce && total <= 11)
  { // добавляем только 10, так как мы уже добавили 1 для туза
   total += 10;
  }

  return total;
}

  ~Hand()
  {
    Clear();
  }
};

//абстрактный класс базового игрока
class GenericPlayer : public Hand
{
  friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);

public:
  GenericPlayer(const string& name = "");

  virtual ~GenericPlayer();

  // чисто виртуальная функция, возвращает информацию, нужна ли игроку
  // еще одна карта
  virtual bool IsHitting() const = 0;

  //возвращает bool значение, есть ли у игрока перебор
  bool IsBusted() const;

  //выводит на экран имя игрока и объявляет, что у него перебор
  void Bust() const;

protected:
  string m_Name;
};

GenericPlayer::GenericPlayer(const string& name): m_Name(name) {}
GenericPlayer::~GenericPlayer() {}

bool GenericPlayer::IsBusted() const
{
  return (GetTotal() > 21);
}
void GenericPlayer::Bust() const
{
  cout << m_Name << " busts.\n";
}


int main(int argc, char *argv[])
{
    cout << "Task 1"<<endl;
//    Реализовать шаблон класса Pair1, который позволяет пользователю передавать данные одного типа парами.
//    Следующий код:
    Pair1 <int> p1(6, 9);
    cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair1<double> p2(3.4, 7.8);
    cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

//    должен производить результат:
//    Pair: 6 9
//    Pair: 3.4 7.8

    cout << endl <<"Task 2" << endl;
//    Реализовать класс Pair, который позволяет использовать разные типы данных в передаваемых парах.
//    Следующий код:

    Pair<int, double> p3(6, 7.8);
    cout << "Pair: " << p3.first() << ' ' << p3.second() << '\n';

    const Pair<double, int> p4(3.4, 5);
    cout << "Pair: " << p4.first() << ' ' << p4.second() << '\n';

//    должен производить следующий результат:
//     Pair: 6 7.8
//     Pair: 3.4 5
//    Подсказка: чтобы определить шаблон с использованием двух разных типов,
//    просто разделите параметры типа шаблона запятой.

    cout << endl <<"Task 3" << endl;
//    Написать шаблон класса StringValuePair, в котором первое значение всегда типа string,
//    а второе — любого типа. Этот шаблон класса должен наследовать частично специализированный
//    класс Pair, в котором первый параметр — string, а второй — любого типа данных.

    StringValuePair<int> svp("Amazing", 7);
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

//    должен производить следующий результат:
//    Pair: Amazing 7
//    Подсказка: при вызове конструктора класса Pair из конструктора класса
//    StringValuePair не забудьте указать, что параметры относятся к классу Pair.

    cout << endl <<"Task 4" << endl;
    cout << "See code" <<endl;
//    Согласно иерархии классов, которая представлена в методичке к уроку 3, от класса Hand
//    наследует класс GenericPlayer, который обобщенно представляет игрока, ведь у нас будет
//    два типа игроков - человек и компьютер. Создать класс GenericPlayer, в который
//    добавить поле name - имя игрока. Также добавить 3 метода:
//    - IsHitting() - чисто виртуальная функция, возвращает информацию, нужна ли игроку
//      еще одна карта.
//    - IsBoosted() - возвращает bool значение, есть ли у игрока перебор
//    - Bust() - выводит на экран имя игрока и объявляет, что у него перебор

    return 0;
}


