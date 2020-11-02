#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: ** 
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA 
// Done by: **
// RE:   **
bool word(string s)
{

    int state = 0;
    int charpos = 0;
    /* replace the following todo the word dfa  ** */
    /*
        state 0 = q0 
        state 1 = qy 
        state 2 = q0q1 
        state 3 = qsa 
        state 4 = qs 
        state 5 = qt
        state 6 = qc
        state 7 = q0qy ?
    */
    while (s[charpos] != '\0')
      {
        //state q0
        //bmknhprg
        if(state == 0 && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'n' || s[charpos] == 'h' || s[charpos] == 'p' || s[charpos] == 'r' || s[charpos] == 'g'))
            {state = 1;}
        //vowels, where i and e can be uppercase 
        else if(state == 0 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'E' || s[charpos] == 'i' || s[charpos] == 'I' || s[charpos] == 'o' || s[charpos] == 'u'))
            {state = 2;}
        //dwzyj
        else if(state == 0 && (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j'))
            {state  = 3;}
        //s
        else if(state == 0 && s[charpos] == 's') 
            {state = 4;}
        //t 
        else if(state == 0 && s[charpos] == 't') 
            {state = 5;}
        //c
        else if(state = 0 && s[charpos] == 'c')
            {state = 6;}
        
        
        
        
        else
        if (state == 1 && s[charpos] == 'b')
        state = 2;
        else
        if (state == 2 && s[charpos] == 'b')
        state = 2;
        else
        return(false);
        charpos++;
      }//end of while

    // where did I end up????
    if (state == 2) return(true);  // end in a final state
     else return(false);
    
}

// PERIOD DFA 
// Done by: **
bool period(string s)
{  // complete this **
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: **

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype { WORD1,WORD2,PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT
    , DESTINATION, PRONOUN, CONNECTOR, ERROR,EOFM };

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = {"WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", 
"WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "ERROR", "EOFM" };

// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.
int rows = 19;
int columns = 19;
string reserved_word[19][19]
{
    {"masu", tokenName[3]},
    {"massen", tokenName[4]},
    {"mashita",  tokenName[5]},
    {"masendeshita", tokenName[6]},
    {"desu", tokenName[7]},
    {"deshita", tokenName[8]},
    {"o", tokenName[9]},
    {"wa", tokenName[10]},
    {"ni", tokenName[11]},
    {"watashi", tokenName[12]},
    {"anata", tokenName[12]},
    {"kare", tokenName[12]},
    {"kanojo", tokenName[12]},
    {"sore", tokenName[12]},
    {"mata", tokenName[13]},
    {"soshite", tokenName[13]},
    {"shikashi", tokenName[13]},
    {"dakara", tokenName[13]},
    {"eofm", tokenName[15]}
};

//string tokenName[30] = { "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS",
//"WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "ERROR", "EOFM" };
tokentype Convert(string str)
{
    if (str == "WORD1")
        return WORD1;
    else if (str == "WORD2")
        return WORD2;
    else if (str == "PERIOD")
        return PERIOD;
    else if (str == "VERB")
        return VERB;
    else if (str == "VERBNEG")
        return VERBNEG;
    else if (str == "VERBPAST")
        return VERBPAST;
    else if (str == "VERBPASTNEG")
        return VERBPASTNEG;
    else if (str == "IS")
        return IS;
    else if (str == "WAS")
        return WAS;
    else if (str == "OBJECT")
        return OBJECT;
    else if (str == "SUBJECT")
        return SUBJECT;
    else if (str == "DESTINATION")
        return DESTINATION;
    else if (str == "PRONOUN")
        return PRONOUN;
    else if (str == "CONNECTOR")
        return CONNECTOR;
}

bool found(tokentype& type, string& w)
{
    for (int i = 0; i < rows; i++)
    {
        if (w == reserved_word[i][0])
        {
            w = reserved_word[i][0];
            type = Convert(reserved_word[i][1]);
            return true;
        }
        else
            return false;
    }
    return false;
}

bool check_last(char w)
{
    switch (w)
    {
    case 'a':
        return true;
    case 'e':
        return true;
    case 'i':
        return true;
    case 'o':
        return true;
    case 'u':
        return true;
    case 'I':
        return true;
    case 'E':
        return true;
    default:
        return false;
    }
}

tokentype getWordType(char c)
{
    switch (c)
    {
    case 'a':
        return WORD1;
    case 'e':
        return WORD1;
    case 'i':
        return WORD1;
    case 'o':
        return WORD1;
    case 'u':
        return WORD1;
    case 'I':
        return WORD2;
    case 'E':
        return WORD2;
    default:
        return ERROR;
    }
}

// ------------ Scanner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: 
int scanner(tokentype& tt, string& w)
{
    // ** Grab the next word from the file via fin
    // 1. If it is eofm, return right now.  
    fin >> w;
    if (w == "eofm")
    {
        return 0;
    }

    /*  **
    2. Call the token functions (word and period)
       one after another (if-then-else).
       Generate a lexical error message if both DFAs failed.
       Let the tokentype be ERROR in that case.

    3. If it was a word,
       check against the reservedwords list.
       If not reserved, tokentype is WORD1 or WORD2
       decided based on the last character.

    4. Return the token type & string  (pass by reference)
    */
    if (word(w))
    {
        if (found(tt, w))
        {
            cout << "Reserved" << endl;
        }
        else if (!found(tt, w))
        {
            if (check_last(w.back()))
            {
                tt = getWordType(w.back());
            }
        }

    }
    else if (period(w))
    {
        //dunno what to do here
    }
    else
    {
        cout << "Lexical Error, Token: " << tokenName[3] << endl;
    }

}//the end of scanner



// The temporary test driver to just call the scanner repeatedly  
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!! 
// Done by:  Louis
int main()
{
    tokentype thetype;
    string theword;
    string filename;

    cout << "Enter the input file name: ";
    cin >> filename;

    fin.open(filename.c_str());

    // the loop continues until eofm is returned.
    while (true)
    {
        scanner(thetype, theword);  // call the scanner which sets
                                    // the arguments  
        if (theword == "eofm") break;  // stop now

        cout << "Type is:" << tokenName[thetype] << endl;
        cout << "Word is:" << theword << endl;
    }

    cout << "End of file is encountered." << endl;
    fin.close();

}// end
