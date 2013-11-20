// Standard Containers
// Map
// Find elements with certain values.

#include <iostream> // debugging
#include <algorithm>
#include <map>

//////////////////////////////////////////////////////////////////////////
// Function object to check the value of map element.
template <typename Key, typename Value>
class ValueEquals
{
  Value val;

public:
  ValueEquals(const Value& _val) //< Initialize value to compare with.
  : val(_val)
  {}

  inline bool operator()(const std::pair<const Key, Value>& element) const
  {
    return element.second == val;
  }
};
//////////////////////////////////////////////////////////////////////////

int main (int argc, char **argv)
{
  typedef std::map<float, float> FFMap; //< float float map
  FFMap myMap;
  FFMap::const_iterator position; //< read only iterator

  //////////////////////////////////////////////////////////////////////////
  // Fill map.
  myMap.insert(std::pair<float, float>(1.0f, 7.0f));  //< use pair for insertion (efficient)
  myMap.insert(FFMap::value_type(2.0f, 4.0f));  //< use value_type for insertion (efficient)
  myMap[3.0f] = 2.0f; //< inefficient insertion - the new value is first initialized by the default value of its type
                      //  which is then overwritten by the correct value.
                      // e.g. - first it inserts 3.0f/float()
                      //      - then it assigns 2.0f
  myMap.insert(FFMap::value_type(4.0f, 3.0f));
  myMap.insert(FFMap::value_type(5.0f, 6.0f));
  myMap.insert(FFMap::value_type(6.0f, 1.0f));
  myMap.insert(FFMap::value_type(7.0f, 3.0f));

  //////////////////////////////////////////////////////////////////////////
  // Search element with KEY 3.0f.
  position = myMap.find(3.0f); //< logarithmic complexity

  if (position != myMap.end()) //< Print if key 3.0f was found.
  {
    std::cout << "Found key: " << position->first << ", its value is: " << position->second << std::endl;
  }

  //////////////////////////////////////////////////////////////////////////
  // Search first element with VALUE 3.0f.
  position = find_if(myMap.begin(), myMap.end(), ValueEquals<float, float>(3.0f)); //< linear complexity

  if (position != myMap.end()) //< Print if value 3.0f was found.
  {
    std::cout << "Found value: " << position->second << " @ key: " << position->first << std::endl;
  }
  // Note that find_if() stops searching as soon as it finds first key with searched value.
  // There is another key with value 3.0f - it is the key 7.0f.

  std::cin.get (); // Nacisnij klawisz, aby zakonczyc program.
  return 0;
}
