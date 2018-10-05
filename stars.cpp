#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::string;
using std::endl;

int main()
{
   bool found = false;

   cout << "Enter file name >> ";
   string fileName;
   std::getline(cin, fileName);

   string properNameLine;
   string properName;
   string properNameTilde;


   int lineNumber {0};
   int indexValue {0};

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
         cout << "Enter proper name: ";
         std::getline(cin, properName);

         while(fin)
         {
            getline(fin, properNameLine);
            int tempFirstTilde = properNameLine.find("~", 0);
            string tempCommonName = properNameLine.substr(0, tempFirstTilde);

            int tempSecondTilde = properNameLine.find("~", tempFirstTilde + 1);
            int tempThirdTilde = properNameLine.find("~", tempSecondTilde + 1);
            string tempProperNameOutput = properNameLine.substr(tempFirstTilde + 1);
            tempProperNameOutput = tempProperNameOutput.substr(0, tempProperNameOutput.find("~", 0));

            if((indexValue = tempProperNameOutput.find(properName, 0)) != string::npos) //searches for propername (the index), it will not equal npos (i.e. -1) when found, -1 elsewhere
            {
               line = properNameLine;
               found = true;
               break;
            }
            lineNumber++;
         }

         fin.clear();
         fin.close();

         if(found == false)
         {
            cout << "No star with the proper name \"" << properName << "\" was found" << endl;
            return -1;
         }

      }
   }


   //EXTRACTING INFORMATION FROM THE STRING

   int firstTilde = line.find("~", 0);
   string commonName = line.substr(0, firstTilde);

   int secondTilde = line.find("~", firstTilde + 1);
   int thirdTilde = line.find("~", secondTilde + 1);
   string properNameOutput = line.substr(firstTilde + 1);
   properNameOutput = properNameOutput.substr(0, properNameOutput.find("~", 0));

   //CREATE A NEW STRING
   string newLine = line.substr(secondTilde + 1, thirdTilde);
   int fourthTilde = newLine.find("~", 0);
   string hrNumber = newLine.substr(0, fourthTilde);
   int fifthTilde = newLine.find("~", fourthTilde + 1);

   //CREATE A THIRD STRING
   string newerLine = newLine.substr(fourthTilde + 1, fifthTilde);
   int sixthTilde = newerLine.find("~", 0);
   string hdNumber = newerLine.substr(0, sixthTilde);

   int lastTilde = line.rfind("~");
   string distance = line.substr(lastTilde + 1);

   //OUTPUT
   cout << "Star: proper name: " << properNameOutput << " distance: " << distance << " light years HD num: " << hdNumber <<
      "\n      HR num: " << hrNumber << " common name: " << commonName << endl;
   return 0;
}

