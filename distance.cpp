#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::string;
using std::endl;

int main()
{
   string tempLine;

   cout << "Enter file name >> ";
   string fileName;
   std::getline(cin, fileName);

   int lineNumber {0};

   double minimumDistance {0};
   double maximumDistance {0};

   string line;
   std::ifstream fin;

   fin.open(fileName);

   if(fin.fail())
   {
      cout << "The file \"" << fileName << "\" does not exist" << endl;
      fin.close();
      return -1;
   }

   else
   {
      if(fin.peek() == EOF)   //CHECKS IF FILE IS EMPTY, peek() goes to the next character, returns EOF if file is empty
      {
         cout << "File \"" << fileName << "\" is empty" << endl;
         return -1;
      }

      else
      {
         double tempDistanceDouble {0};
         int counter {0};

         string tempMinimumDistance;
         string tempMaximumDistance;

         cout << "Enter minimum distance >> ";
         getline(cin, tempMinimumDistance);
         cout << "Enter maximum distance >> ";
         getline(cin, tempMaximumDistance);

         minimumDistance = std::stod(tempMinimumDistance);
         maximumDistance = std::stod(tempMaximumDistance);

         if(minimumDistance < 0 || maximumDistance < 0)
         {
            if(maximumDistance < 0 && minimumDistance < 0)
            {
               cout << "Both distances are less than 0" << endl;
               return -1;
            }
            else if(minimumDistance < 0)
            {
               cout << "Minimum distance must be greater than or equal to 0" << endl;
               return -1;
            }
            else if(maximumDistance < 0)
            {
               cout << "Maximum distance must be greater than or equal to 0" << endl;
               return -1;
            }
         }

         if(minimumDistance > maximumDistance)
         {
            cout << "Maximum distance is lower than the minimum distance, thus no stars could be found" << endl;
            return -1;
         }

         while(fin)
         {
            getline(fin, tempLine);

            int lastTilde = tempLine.rfind("~");
            string tempDistanceString = tempLine.substr(lastTilde + 1);

            if(!tempDistanceString.empty())
            {
               tempDistanceDouble = std::stod(tempDistanceString);
            }

            if(tempDistanceDouble <= maximumDistance && tempDistanceDouble >= minimumDistance && !tempLine.empty())
            {
               counter++;  //Increment Counter
               
               //EXTRACTING INFORMATION FROM THE LINE
               int firstTilde = tempLine.find("~", 0);
               string commonName = tempLine.substr(0, firstTilde);

               int secondTilde = tempLine.find("~", firstTilde + 1);
               int thirdTilde = tempLine.find("~", secondTilde + 1);
               string properName = tempLine.substr(firstTilde + 1);
               properName = properName.substr(0, properName.find("~", 0));

               //CREATE A NEW STRING
               string newTempLine = tempLine.substr(secondTilde + 1, thirdTilde);
               int fourthTilde = newTempLine.find("~", 0);
               string hrNumber = newTempLine.substr(0, fourthTilde);
               int fifthTilde = newTempLine.find("~", fourthTilde + 1);

               //CREATES ANOTHER NEW STRING
               string newerTempLine = newTempLine.substr(fourthTilde + 1, fifthTilde);
               int sixthTilde = newerTempLine.find("~", 0);
               string hdNumber = newerTempLine.substr(0, sixthTilde);
               int seventhTilde = newerTempLine.find("~", sixthTilde);
               string distance = newerTempLine.substr(seventhTilde + 1);
               double tempDistance = std::stod(tempDistanceString);

               cout << "Star: proper name: " << properName << " distance: " << std::setprecision(6) << tempDistance << " light years HD num: " << hdNumber
                    << "\n      HR num: " << hrNumber << " common name: " << commonName << endl;

            }
         }

         fin.close();

         if(counter == 0)
         {
            cout << "No star within " << minimumDistance << " and " << maximumDistance << " light years was found" << endl;
         }

      }
   }

   return 0;
}
