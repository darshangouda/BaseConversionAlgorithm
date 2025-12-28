#include<iostream>
#include<string.h>
//#include<stdio.h>
//#include<stdlib.h>


using namespace std;

const char DIGITS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";


const long int MAX = 30000;
char inputString[4094];//console/terminal buffer limitation

// ---------------------------
// Renamed arrays
// ---------------------------
unsigned int integerWork[MAX]   = {0};
unsigned int fractionWork[MAX]  = {0};
unsigned int fractionOut[MAX]   = {0};

// --------------------------------------------------
void display(long int n, long int f)
{
    long int k;
    for (k = n; k >= 0; k--){
        cout << DIGITS[ integerWork[k] ];
        //cout << integerWork[k] <<"|";
        }

    // Only print fractional part if f >= 0 (meaning some fractional digits were produced)
    if (f >= 0 && !(f == 0 && fractionOut[0] == 0))
    {
        cout << ".";
        for (k = 0; k <= f; k++)
            cout << DIGITS[ fractionOut[k] ];
    }
    cout << endl;
}
// --------------------------------------------------

int main()
{

    long int i, k, p;


    long int base1, base2, maxDigitBase2;
    long int integerInputLen = 0;
    long int fractionInputLen = 0;

    long int highestIntPos;
    long int fracLen;            // will hold final fractional length (can be -1 if none)

    long int fractionLimit = 100;

    int choice = 0;

    long int intLenProcessed, carryIndex;

    base1 = 10;
    base2 = 16;

    maxDigitBase2 = base2 - 1;

begining:



    // clear buffers
    for (p = 0; p < MAX; p++)
    {
        inputString[p] = 0;
        integerWork[p] = 0;
        fractionWork[p] = 0;
        fractionOut[p] = 0;
    }

    cout << "________________________________________________________________________________________________________________" << endl;
    cout << "                 DATA REPRESENTATION" << endl;
    cout << "1.CONVERT  BASE1=" << base1 << "  TO  BASE2=" << base2 << " \n FRACTION LIMIT =" << fractionLimit <<endl;
    cout << "2.CHANGE THE BASE , FRACTION LIMIT" << endl;
    cout << "3.CLEAR SCREEN " << endl;
    cout << "4.EXIT " << endl;
    cout << "ENTER YOUR CHOICE = ";
    cin >> choice;

    if (choice == 1)
        goto case1_start;
    else if (choice == 2)
    {
        cout << "BASE1 = ";
        cin >> base1;
        cout << "BASE2 = ";
        cin >> base2;
        cout << "FRACTION LIMIT = ";
        cin >> fractionLimit;
        maxDigitBase2 = base2 - 1;
        goto begining;
    }
    else if (choice == 3)
    {
        system("cls");
        goto begining;
    }
    else if (choice == 4)
    {
        exit(0);
    }
    else
    {
        cout << "INVALID CHOICE\n";
        goto begining;
    }

case1_start:

    cout << "ENTER NUMBER (base" << base1 << "): "<<endl;
    cin >> inputString;

    integerInputLen = strlen(inputString);
    cout << "LENGTH = " << integerInputLen << endl;

    // find decimal point
    for (p = 0; p < integerInputLen; p++)
        if (inputString[p] == '.')
            break;

    // convert ASCII to numeric (in-place)
    for (i = 0; i < integerInputLen; i++)
    {
        if (inputString[i] >= '0' && inputString[i] <= '9')
        {
            inputString[i] = inputString[i] - '0';
        }
        else if (inputString[i] >= 'A' && inputString[i] <= 'Z')
        {
            inputString[i] = inputString[i] - 'A' + 10;   // 10–35
        }
        else if (inputString[i] >= 'a' && inputString[i] <= 'z')
        {
            inputString[i] = inputString[i] - 'a' + 36;   // 36–61
        }
    }


    // copy fraction part reverse into fractionWork[]
    k = 0;
    for (i = integerInputLen - 1; i > p; i--)
        fractionWork[k++] = inputString[i];

    //cout << "please wait(processing...)" << endl;

    fractionInputLen = integerInputLen - p -1;
    integerInputLen  = p;

    carryIndex = 1;
    fracLen = -1;
    intLenProcessed = 1;

    // ---------------------------------------------------
    // INTEGER PART CONVERSION
    // ---------------------------------------------------
    for (k = 0; k < integerInputLen; k++)
    {
        for (p = 0; (integerWork[p] *= base1), p <= intLenProcessed; p++) {}

        integerWork[0] += inputString[k];

        for (i = 0; i <= intLenProcessed; i++)
        {
            long int idx = i;
            while (integerWork[idx] > maxDigitBase2)
            {
                integerWork[idx+1] += integerWork[idx] / base2;
                integerWork[idx]   %= base2;
                idx++;
            }
            if (carryIndex < idx) carryIndex = idx;
        }
        intLenProcessed = carryIndex;
    }

    // ---------------------------------------------------
    // FRACTIONAL PART
    // ---------------------------------------------------
    long int fractionResultIndex = -1;
    bool fractionNotZero = true;

    // Only run fractional loop if there was a fractional part in the input
    if (fractionInputLen > 0 && fractionLimit>0)
    {
        do
        {
            for (p = 0; p < fractionInputLen; p++)
            {
                fractionWork[p] *= base2;
            }
            for (i = 0; i < fractionInputLen; i++)
            {
                fractionWork[i + 1] += fractionWork[i] / base1;
                fractionWork[i] %= base1;
            }


            // store extracted digit
            fractionOut[++fractionResultIndex] = fractionWork[fractionInputLen];

            // CORRECT: clear working buffer (not fractionOut)
            fractionWork[fractionInputLen] = 0;
            fractionNotZero = false;
            for (p = 0; p < fractionInputLen; p++)
            {
                if (fractionWork[p] != 0)
                {
                    fractionNotZero = true;
                    break;
                }
            }
        }
        while (fractionNotZero && fractionResultIndex < fractionLimit - 1);
    }

    // set final fracLen to produced index (can be -1 if no fraction produced)
    fracLen = fractionResultIndex;

    highestIntPos = 0;
    for (p = 0; p < MAX; p++)
        if (integerWork[p] > 0)
            highestIntPos = p;

    cout << endl << "EQUIVALENT TO (base" << base2 <<")"<< endl;
    display(highestIntPos, fracLen);
    goto begining;

    return 0;
}

