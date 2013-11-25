// STL Containers
// Set

// Compilation using GCC compiler under Windows.
// g++ -std=c++0x set.cpp -o set.exe

#include <iostream> // debugging
#include <set>

// 1. Set container

// Function object
class SortCriterion
{
  public:
  inline bool operator()(int a, int b) const
  {
    return (a < b) ? false : true;
  }
};

class Rocket
{
  float m0; // The initial total mass, including propellant.

public:
  explicit Rocket(float _m0)
  : m0(_m0)
  {}

  // Sorting criterion for rockets i.e.: binary < operator overload.
  inline bool operator<(const Rocket& r) const
  {
    const Rocket* pRocket = this;
    return (pRocket->m0 < r.m0) ? false : true;
  }

  inline float GetTotalMass() const { return m0; }
};

int main (int argc, char **argv)
{
  // c++0x simple Lambda.
  auto AddSeparator = [] () { std::cout << "-----------" << std::endl; };

  const int array[] = { 2, 1, 155, 3 };

  // Copy all elements of the array into a set.
  const std::set<int> setOfInts(array, array + sizeof(array)/sizeof(array[0]));

  // Read only iterator.
  std::set<int>::const_iterator it = setOfInts.begin();
  for (it; it != setOfInts.end(); ++it)
  {
    std::cout << *it << std::endl;
  }

  /////////////////////////////////////////////////////////////////////////////
  AddSeparator();

  const std::set<int, SortCriterion> setOfIntsDescending(array, array + sizeof(array)/sizeof(array[0]));

  // c++0x range-for-statement
  for (auto x : setOfIntsDescending)
    std::cout << x << std::endl;

  ///////////////////////////////////////////////////////////////////////////
  AddSeparator();

  std::set<Rocket> setOfRockets;

  const Rocket saturn (12.5f);
  const Rocket atlas  (128.75f);
  const Rocket proton (71.5f);
  const Rocket vostok (828.03f);

  setOfRockets.insert(saturn);
  setOfRockets.insert(atlas);
  setOfRockets.insert(proton);
  setOfRockets.insert(vostok);

  // Print rockets.
  for (auto rocket : setOfRockets)
    std::cout << "Total mass, including propellant: " << rocket.GetTotalMass() << std::endl;

  std::cin.get (); // Press any key to continue . . .
  return 0;
}
