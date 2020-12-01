#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.  
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .  
       and then append the two files into one: 
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//=================================================
// File parser.cpp written by Group Number: 26
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.  

bool traceFlag;

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme
enum tokentype {
    WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS,
    OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, ERROR, EOFM
};

bool word(string s)
{
    int state = 0;
    int charpos = 0;

    while (s[charpos] != '\0')
    {
        //state 0 = q0
        //vowels, where i and e can be uppercase 
        if (state == 0) {
            if (state == 0 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'E' || s[charpos] == 'i' || s[charpos] == 'I' || s[charpos] == 'o' || s[charpos] == 'u'))
            {
                state = 1;
            }
            //bmknhprg
            else if (state == 0 && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'n' || s[charpos] == 'h' || s[charpos] == 'p' || s[charpos] == 'r' || s[charpos] == 'g'))
            {
                state = 2;
            }
            //dwzyj
            else if (state == 0 && (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j'))
            {
                state = 3;
            }
            //s
            else if (state == 0 && s[charpos] == 's')
            {
                state = 4;
            }
            //t 
            else if (state == 0 && s[charpos] == 't')
            {
                state = 5;
            }
            //c
            else if (state == 0 && s[charpos] == 'c')
            {
                state = 6;
            }
            else break;
        }
        else if (state == 1)
        {
            //state 1 = q0q1 
            if (state == 1 && s[charpos] == 'n')
            {
                state = 7;
            } // --> q0qy
            else if (state = 1 && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'n' || s[charpos] == 'h' || s[charpos] == 'p' || s[charpos] == 'r' || s[charpos] == 'g'))
            {
                state = 2;
            }
            else if (state = 1 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'E' || s[charpos] == 'i' || s[charpos] == 'I' || s[charpos] == 'o' || s[charpos] == 'u'))
            {
                state = 1;
            }
            else if (state == 0 && (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j'))
            {
                state = 3;
            }
            else if (state == 0 && s[charpos] == 's')
            {
                state = 4;
            }
            else if (state == 0 && s[charpos] == 't')
            {
                state = 5;
            }
            else if (state == 0 && s[charpos] == 'c')
            {
                state = 6;
            }
            else break;
        }
        else if (state == 2)
        {
            //state 2 = qy 
            if (state == 2 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'E' || s[charpos] == 'i' || s[charpos] == 'I' || s[charpos] == 'o' || s[charpos] == 'u'))
            {
                state = 1;
            }
            else if (state == 2 && s[charpos] == 'y')
            {
                state = 3;
            }
            else break;
        }
        else if (state == 3)
        {
            //state 3 = qsa 
            if (state == 3 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'E' || s[charpos] == 'i' || s[charpos] == 'I' || s[charpos] == 'o' || s[charpos] == 'u'))
            {
                state = 1;
            }
            else break;
        }
        else if (state == 4)
        {
            //state 4 = qs
            if (state == 4 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'E' || s[charpos] == 'i' || s[charpos] == 'I' || s[charpos] == 'o' || s[charpos] == 'u'))
            {
                state = 1;
            }
            else if (state == 4 && s[charpos] == 'h')
            {
                state = 3;
            }
            else break;
        }
        else if (state == 5)
        {
            //state 5 = qt 
            if (state == 5 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'E' || s[charpos] == 'i' || s[charpos] == 'I' || s[charpos] == 'o' || s[charpos] == 'u'))
            {
                state = 1;
            }
            else if (state == 5 && s[charpos] == 's')
            {
                state = 3;
            }
            else break;
        }
        else if (state == 6)
        {
            //state 6 = qc
            if (state = 6 && s[charpos] == 'h')
            {
                state = 3;
            }
            else break;
        }
        else if (state == 7)
        {

            //state 7 = q0qy
            if (state == 7 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'E' || s[charpos] == 'i' || s[charpos] == 'I' || s[charpos] == 'o' || s[charpos] == 'u'))
            {
                state = 1;
            }
            else if (state == 7 && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'n' || s[charpos] == 'h' || s[charpos] == 'p' || s[charpos] == 'r' || s[charpos] == 'g'))
            {
                state = 2;
            }
            else if (state == 7 && (s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j'))
            {
                state = 3;
            }
            else if (state == 7 && s[charpos] == 's')
            {
                state = 4;
            }
            else if (state == 7 && s[charpos] == 't')
            {
                state = 5;
            }
            else if (state = 7 && s[charpos] == 'c')
            {
                state = 6;
            }
            else break;
        }

        //end of while
        charpos++;
    }
    // where did I end up????
    // want to be in q0q1 | q0qy 
    if (state == 1 || state == 7) return(true);  // end in a final state
    else return(false);
}

// PERIOD DFA 
// Done by: 
bool period(string s)
{  // complete this **
    if (s == ".")
        return true;
    return false;
}

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = { "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS",
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
    else if (str == "ERROR")
        return ERROR;
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
    case 'n':
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
    case 'n':
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
// ** Done by: Josh Mumford, 
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
            //cout << "Reserved" << endl;
            cout << "Scanner called using the word: " << w << endl;
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
        tt = PERIOD;
    }
    else
    {
        cout << "Lexical Error, " << w << " is not a valid token." << endl;
        tt = Convert(tokenName[14]);
    }

}//the end of scanner


// Type of error: Unexpected token
// Done by: Trey Stone
void syntaxerror1(string inputLexeme, tokentype expectedToken){
    if (traceFlag) cout << "SYNTAX ERROR: expected " << tokenName[expectedToken] << "but found " << inputLexeme << endl;
    exit(1);
}
// Type of error: Unknown token
// Done by: Trey Stone
void syntaxerror2(string inputLexeme, string functionName) {
    if (traceFlag) cout << "SYNTAX ERROR: unexpected " << inputLexeme << "found in " << functionName << endl;
    exit(1);
}

string saved_lexeme;
tokentype saved_token;
bool token_available;

// Purpose: To look ahead to check the next token from the scanner. 
//Returns the saved_token but does not eat up the token.
// Done by: Josh Mumford
tokentype next_token()
{
    //declare a bool to check if there is a saved token
   // bool token_available = false;

    //if there is no saved token
    if (!token_available)
    {
        //call the scanner to grab new token and save word to saved_lexeme
        //set token_available to true
        scanner(saved_token, saved_lexeme);
        //saved_lexeme = saved_lexeme;
        token_available = true;

        //if the token is an ERROR call syntaxerror1
        if (saved_token == ERROR)
        {
            syntaxerror1(saved_lexeme, saved_token);
        }
    }
    //return the token
    return saved_token;
}

// Purpose: Checks and uses the expected token. Compares the expected to the next_token.
//If different generate a syntax error and handle the error.
//else set the token_available bool to false and return true
// Done by: Josh Mumford, Trey Stone
bool match(tokentype expected) 
{
    //if the next_token and the expected do not match. generate syntax error
    //else set token_available to false and display the matched token
    //returns true if succeeds

    tokentype next = next_token();

    if (next != expected)
        syntaxerror1(saved_lexeme, next);
    else
    {
        token_available = false;
        if (traceFlag) cout << "Matched " << tokenName[saved_token] << endl;
        return true;
    }
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: <noun> ::= WORD1 | PRONOUN
// Done by: Josh Mumford
void noun_non_term()
{
    if (traceFlag) cout << "Processing <noun>" << endl;
    switch (next_token())
    {
    case WORD1:
        match(WORD1);
        break;
    case PRONOUN:
        match(PRONOUN);
        break;
    default:
        syntaxerror2(saved_lexeme, "noun");
    }
}

// Grammar: <verb> ::= WORD2
// Done by: Josh Mumford, Trey Stone
void verb_non_term()
{
    if (traceFlag) cout << "Processing <verb>" << endl;
    switch (next_token())
    {
    case WORD2:
        match(WORD2);
        break;
    default:
        syntaxerror2(saved_lexeme, "verb");
    }
}

// Grammar: <be> ::= IS | WAS
// Done by: Josh Mumford
void be_non_term()
{
    if (traceFlag) cout << "Processing <be>" << endl;
    switch (next_token())
    {
    case IS:
        match(IS);
        break;
    case WAS:
        match(WAS);
        break;
    default:
        syntaxerror2(saved_lexeme, "be");
    }
}

// Grammar: <tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: Josh Mumford
void tense_non_term()
{
    if (traceFlag) cout << "Processing <tense>" << endl;
    switch (next_token())
    {
    case VERBPAST:
        match(VERBPAST);
        break;
    case VERBPASTNEG:
        match(VERBPASTNEG);
        break;
    case VERB:
        match(VERB);
        break;
    case VERBNEG:
        match(VERBNEG);
        break;
    default:
        syntaxerror2(saved_lexeme, "tense");
    }
}

// Grammar: <after destination> ::= <verb> <tense> PERIOD
// Done by: Trey Stone
void after_destination_non_term()
{
    if (traceFlag) cout << "Processing <after destination>" << endl;
    switch (next_token())
    {
    case WORD2:
        verb_non_term();
        tense_non_term();
        match(PERIOD);
        break;
    default:
        if (traceFlag) syntaxerror2(saved_lexeme, "after_destination");
    }
}

// Grammar: <after object> ::= <after destination> | <noun> DESTINATION <after destination>
// Done by: Trey Stone
void after_object_non_term()
{
    if (traceFlag) cout << "Processing <after object>" << endl;
    switch (next_token())
    {
    case WORD2:
        after_destination_non_term();
        break;
    case WORD1:
    case PRONOUN:
        noun_non_term();
        match(DESTINATION);
        after_destination_non_term();
    default:
        syntaxerror2(saved_lexeme, "after_object");
    }
}

// Grammar: <after noun> ::= <be> PERIOD | DESTINATION <after destination> | OBJECT <after object>
// Done by: Trey Stone
void after_noun_non_term()
{
    if (traceFlag) cout << "Processing <after noun>" << endl;
    switch (next_token())
    {
    case IS:
    case WAS:
        be_non_term();
        match(PERIOD);
        break;
    case DESTINATION:
        match(DESTINATION);
        after_destination_non_term();
    case OBJECT:
        match(OBJECT);
        after_object_non_term();
        break;
    default:
        syntaxerror2(saved_lexeme, "after_noun");
    }
}

// Grammar: <after subject> ::= <verb> <tense> PERIOD | <noun> <after noun>
// Done by: Trey Stone
void after_subject_non_term()
{
    if (traceFlag) cout << "Processing <after subject>" << endl;
    switch (next_token())
    {
    case WORD2:
        verb_non_term();
        tense_non_term();
        match(PERIOD);
        break;
    case WORD1:
    case PRONOUN:
        noun_non_term();
        after_noun_non_term();
        break;
    default:
        syntaxerror2(saved_lexeme, "after_subject");
    }
}

void s()
{
    switch (next_token())
    {
    case CONNECTOR:
        match(CONNECTOR);
        break;
    case WORD1:
        noun_non_term();
        break;
    case PRONOUN:
        noun_non_term();
        break;
    }

    match(SUBJECT);
    after_subject_non_term();
}

// Grammar: <story> ::= <s> {<s>}
// Done by: Elisha Nicolas
void story_non_term() 
{
   cout << "Processing <story>" << endl; 
   s(); 
   while (true)
   {
      if(next_token() == EOFM)
      {
        cout << "Successfully Parsed <story>" << endl; 
         break; 
      }
   }
}

string filename;

//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by: Elisha Nicolas, Trey Stone
int main()
{
    cout << "Enter the input file name: ";
    cin >> filename;
    fin.open(filename.c_str());
    if (fin.is_open())
        cout << "open!!" << endl;
    else
        cout << "file not found" << endl;

    char traceChar;

trace:
    cout << "Print tracing messages? (y/n): ";
    cin >> traceChar;

    switch (traceChar)
    {
    
    case 'y':
    case 'Y':
        traceFlag = true;
        break;
    case 'n':
    case 'N':
        traceFlag = false;
        break;
    default:
        goto trace;
    }

    story_non_term();

    fin.close();

    //** calls the <story> to start parsing
    //** closes the input file 

}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions


