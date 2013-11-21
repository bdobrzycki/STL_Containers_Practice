// STL Containers
// Map

#include <iostream> // debugging
#include <assert.h> // debugging
#include <string>
#include <map>

// 1. Map container manages key/value pairs of elements.
// 2. Map sorts its elements automatically according to a certain sorting
//    criterion that is used for the actual key.
// 3. Default criterion "less" is used.

//////////////////////////////////////////////////////////////////////////
// Print all map elements.
void PrintStringFloatMap(const std::map<std::string, float>& m)
{
  // Use read-only iterator.
  std::map<std::string, float>::const_iterator readPos;

  for (readPos = m.begin(); readPos != m.end(); ++readPos)
  {
    std::cout << "stock: " << readPos->first << "\t";       //< key
    std::cout << "price: " << readPos->second << std::endl; //< value
  }

  std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////
// Data to be stored inside map container.
class Book
{
public:
  int numOfPages;
  std::string author;

  Book(){}
  Book(const std::string& _author, int _numOfPages)
    :author(_author), numOfPages(_numOfPages)
  {}
};

//////////////////////////////////////////////////////////////////////////
// Function object.
class SortCriterionAuthorName
{
public:
  inline bool operator()(const std::string& authorName1, const std::string& authorName2) const
  {
    return authorName1 < authorName2;
  }
};

//////////////////////////////////////////////////////////////////////////
// Function object.
class SortCriterionPages
{
public:
  inline bool operator()(int numOfPages1, int numOfPages2) const
  {
    return numOfPages1 > numOfPages2;
  }
};

//////////////////////////////////////////////////////////////////////////
int main (int argc, char **argv)
{
  // Shows the use of map as an associative array.
  // The map is used as a stock chart. The elements of the map are pairs
  // in which the key is the name of the stock and the value is its price.

  // Create map / associative array
  // - keys are strings
  // - values are floats

  std::map<std::string, float> stocks; //< Create empty container.

  // Insert some elements:
  stocks["VW"]      = 413.5f;
  stocks["SpaceX"]  = 713.5f;
  stocks["Tesla"]   = 813.5f;
  stocks["Siemens"] = 813.5f;
  stocks["BASF"]    = 369.5f;

  PrintStringFloatMap(stocks);
  // Note that the map elements are sorted alphabetically.

  // Modification of the value of elements stored in map container.
  std::map<std::string, float>::iterator pos;

  // Double all the prices.
  for (pos = stocks.begin(); pos != stocks.end(); ++pos)
  {
    pos->second *= 2.0f;
  }

  PrintStringFloatMap(stocks);

  /* Rename "VW" to "Volkswagen".
   * It is only possible by exchanging an element.
   */
  stocks["Volkswagen"] = stocks["VW"];
  stocks.erase("VW");

  PrintStringFloatMap(stocks);

  //////////////////////////////////////////////////////////////////////////
  // Bespoke sorting criterion - use function object.
  //////////////////////////////////////////////////////////////////////////
  // Make data - books.
  const Book b1("Jazar", 1578);
  const Book b2("Allerton", 347);
  const Book b3("Stroustrup", 1345);
  const Book b4("Matyka", 79);

  //////////////////////////////////////////////////////////////////////////
  // Book catalog 1: books sorted by the author's name.
  // NOTE: Map sorts its elements automatically according to a certain sorting
  // criterion that is used for the actual KEY (here Key is std::string - author name).
  // Function object SortCriterionAuthorName needs to be able to compare keys (strings in this case).

  std::map<std::string, Book, SortCriterionAuthorName> bookCatalog1;

  // Fill map.
  bookCatalog1[b1.author] = b1;
  bookCatalog1[b2.author] = b2;
  bookCatalog1[b3.author] = b3;
  bookCatalog1[b4.author] = b4;

  // Read map.
  std::map<std::string, Book, SortCriterionAuthorName>::const_iterator bookIter1;
  for (bookIter1 = bookCatalog1.begin(); bookIter1 != bookCatalog1.end(); ++bookIter1)
  {
    std::cout << "Key: "     << bookIter1->first << "\t";  //< key
    std::cout << "Author: "  << bookIter1->second.author <<
                 ", pages: " << bookIter1->second.numOfPages << std::endl;  //< value
  }
  std::cout << std::endl;

  //////////////////////////////////////////////////////////////////////////
  // Book catalog 2: books sorted by the number of pages.
  // NOTE: Map sorts its elements automatically according to a certain sorting
  // criterion that is used for the actual KEY (here the key is an int - number of pages).
  // Function object SortCriterionPages needs to be able to compare keys (integers in this case).

  std::map<int, Book, SortCriterionPages> bookCatalog2;

  // Fill map (various ways).

  bookCatalog2[b1.numOfPages] = b1;  //< inefficient insertion
  // the new value is first initialized by the default value of its type
  // which is then overwritten by the correct value.
  // e.g. - first it inserts numOfPages/Book() (default Book constructor)
  //      - then it assigns values

  // use value_type for insertion (efficient)
  bookCatalog2.insert(std::map<int, Book, SortCriterionPages>::value_type(b2.numOfPages, b2));

  bookCatalog2.insert(std::make_pair(b3.numOfPages, b3));  //< use make_pair for insertion (efficient)

  bookCatalog2.insert(std::pair<int, Book>(b4.numOfPages, b4));  //< use pair for insertion (efficient)

  // Any attempt to insert a new element to the map with a key that has already been added will fail.
  // This is the way to check whether the insertion was successful:
  // i.e. the member second of pair structure returns whether the insertion was successful.

  // assert(bookCatalog2.insert(std::make_pair(b4.numOfPages, b4)).second && "Insertion failed!");

  // Read map.
  std::map<int, Book, SortCriterionPages>::iterator bookIter2;
  for (bookIter2 = bookCatalog2.begin(); bookIter2 != bookCatalog2.end(); ++bookIter2)
  {
    std::cout << "Key: "     << bookIter2->first << "\t";  //< key
    std::cout << "Author: "  << bookIter2->second.author <<
                 ", pages: " << bookIter2->second.numOfPages << std::endl;  //< value
  }

  std::cin.get (); // Nacisnij klawisz, aby zakonczyc program.
  return 0;
}
