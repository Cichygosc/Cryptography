#include <iostream>
#include <vector>
#include <bitset>
#include <cctype>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

void xorFunc(const string & a, const vector<unsigned long> & keys, const int & startingKey, string & result)
{
	unsigned char * cString = (unsigned char*)(a.c_str());
	for (size_t i = 0; i < a.size(); ++i)
	{
		if (i + startingKey >= keys.size())
		{
			break;
		}
		result += (*(cString + i) ^ keys[i + startingKey]);
	}
}

bool hasSpecialChar(const string & str)
{
	return find_if(str.begin(), str.end(),
		[](char ch) { return !(isalpha(ch) || ch == ' '); }) != str.end();
}

void init(const vector<string> & words, const vector<vector<unsigned long>> & ciphers)
{
	ofstream resultFile("result.txt");

	vector<unsigned long> cipher1 = ciphers.back();
	for (size_t k = 0; k < ciphers.size() - 1; ++k)
	{
		vector<unsigned long> cipher2 = ciphers[k];
		vector<unsigned long> ciphersXOR;
		size_t shorterLength = cipher1.size() > cipher2.size() ? cipher2.size() : cipher1.size();
		for (size_t j = 0; j < shorterLength; ++j)
		{
			ciphersXOR.push_back(cipher1[j] ^ cipher2[j]);
		}

		for (size_t j = 0; j < words.size(); ++j)
		{
			string word = words[j];
			size_t wordSize = word.size();
			for (size_t l = 0; l < ciphersXOR.size() - wordSize; ++l)
			{
				string result;
				xorFunc(word, ciphersXOR, l, result);
				if (!hasSpecialChar(result))
				{
					resultFile << "Found word: " << result << " from word " << word << " starting at position " << l << " cipher " << k << " \n";
				}
			}
		}
	}		

	resultFile.close();
}

void checkWord(const string & word, const vector<vector<unsigned long>> & ciphers, const int & position, size_t cipherIndex)
{
	cout << "\nFor word " << word << endl;
	string key;
	xorFunc(word, ciphers[cipherIndex], position, key);
	for (size_t i = 0; i < ciphers.size(); ++i)
	{
		string result;
		xorFunc(key, ciphers[i], position, result);
		cout << i << ": " << result <<  endl;
	}
}

int main()
{
	ifstream wordsFile("w.txt");
	vector<string> words;
	if (wordsFile.is_open())
	{
		string word;
		while (getline(wordsFile, word))
		{
			words.push_back(word);
		}
		wordsFile.close();
	}
	else
	{
		return -1;
	}

	ifstream ciphersFile("ciphers.txt");
	vector<vector<unsigned long>> ciphers;
	if (ciphersFile.is_open())
	{
		string cipher;
		while (getline(ciphersFile, cipher))
		{
			istringstream iss(cipher);
			vector<unsigned long> bytes;
			string byte;
			while (getline(iss, byte, ' '))
			{
				bitset<8> b(byte);
				bytes.push_back(b.to_ulong());
			}
			ciphers.push_back(bytes);
		}
		ciphersFile.close();
	}
	else
	{
		return -1;
	}

	init(words, ciphers);

	checkWord(" and ", ciphers, 87, 2);
	checkWord("measure ", ciphers, 87, 6);
	checkWord(" was great", ciphers, 87, 10);
	checkWord(" Farewell; co", ciphers, 84, 4);
	checkWord(" I rather weep", ciphers, 83, 19);
	checkWord(" I Were in a ma", ciphers, 82, 1);
	checkWord(" find those that ", ciphers, 81, 16);
	checkWord(" maidenhead, at twelve", ciphers, 79, 11);
	checkWord(" business was great; and", ciphers, 78, 10);
	checkWord(" I'll find those that shall", ciphers, 76, 16);
	checkWord(" sweet repose and rest Come t", ciphers, 74, 2);
	checkWord(" thousand years, I never should ", ciphers, 71, 17);
	checkWord(" yourself and I Were in a mask? S", ciphers, 69, 1);
	checkWord(" Mercutio, my business was great; and", ciphers, 65, 10);
	checkWord(" ROMEO", ciphers, 62, 13);
	checkWord(" sadness, who is that you love. ROMEO", ciphers, 61, 18);
	checkWord(" good night! as sweet repose and rest C", ciphers, 59, 2);
	checkWord(" should live a thousand years, I never should ", ciphers, 57, 17);
	checkWord(" ROMEO ROMEO", ciphers, 56, 13);
	checkWord(" Sometime she gallops o'er a courtier's nose, And the", ciphers, 50, 7);
	checkWord(" ROMEO", ciphers, 47, 12);
	checkWord(" ROMEO Pardon, good Mercutio, my business was great; and ", ciphers, 46, 10);
	checkWord(" ROMEO I fear, too early: for my mind misgives Some conseque", ciphers, 43, 9);
	checkWord(" BENVOLIO Tell me in sadness, who is that you love. ROMEO ", ciphers, 41, 18);
	checkWord(" Farewell; be trusty, and I'll quit thy pains: Farewell; commend ", ciphers, 38, 4);
	checkWord(" conceive? ROMEO Pardon, good Mercutio, my business was great; and ", ciphers, 36, 10);
	checkWord(" tell me who. ROMEO", ciphers, 34, 12);
	checkWord(" daughter? call her forth to me. Nurse Now, by my maidenhead, at twelve y", ciphers, 30, 11);
	checkWord(" sadly tell me who. ROMEO", ciphers, 28, 12);
	checkWord(" Exit Romeo", ciphers, 27, 15);
	checkWord(" dancing days: How long is't now since last yourself and I Were in a mask? Se", ciphers, 26, 1);
	checkWord(" than he is, and twenty such Jacks; and if I cannot, I'll find those that shall", ciphers, 24, 16);
	checkWord(" shall come about! I warrant, an I should live a thousand years, I never should ", ciphers, 23, 17);
	checkWord(" villain Romeo. CAPULET Content thee, gentle coz, let him alone;", ciphers, 20, 0);
	checkWord(" where's my daughter? call her forth to me. Nurse Now, by my maidenhead, at twelve y", ciphers, 19, 11);
	checkWord(" lustier than he is, and twenty such Jacks; and if I cannot, I'll find those that shall", ciphers, 16, 16);
	checkWord("beauteous flower when next we meet. Good night, good night! as sweet repose and rest Come t", ciphers, 12, 2);
	checkWord(" were lustier than he is, and twenty such Jacks; and if I cannot, I'll find those that shall", ciphers, 11, 16);
	checkWord(" prompter, for our entrance: But let them measure us by what they will; We'll measure them a m", ciphers, 9, 6);
	checkWord(" commend me to thy lady and mistress. I protest unto thee-- Nurse Good heart, and, i' faith, I wi", ciphers, 6, 5);
	checkWord(" CAPULET Nurse, where's my daughter? call her forth to me. Nurse Now, by my maidenhead, at twelve y", ciphers, 4, 11);
	checkWord("CAPULET He shall be endured: What, goodman boy! I say, he shall: go to; Am I the master here, or you? g", ciphers, 0, 8);
	checkWord("Supper is done, and we shall come too late. ROMEO I fear, too early: for my mind misgives Some consequence ", ciphers, 0, 9);
	checkWord("To see, now, how a jest shall come about! I warrant, an I should live a thousand years, I never should forget ", ciphers, 0, 17);
	checkWord("LADY CAPULET Nurse, where's my daughter? call her forth to me. Nurse Now, by my maidenhead, at twelve year old ", ciphers, 0, 11);
	checkWord("Because their breaths with sweetmeats tainted are: Sometime she gallops o'er a courtier's nose, And then dreams", ciphers, 0, 7);
	checkWord("To see, now, how a jest shall come about! I warrant, an I should live a thousand years, I never should forget it", ciphers, 0, 17);
	checkWord("For you and I are past our dancing days: How long is't now since last yourself and I Were in a mask? Second Capulet", ciphers, 0, 1);
	checkWord("What I have spoke: but farewell compliment! Dost thou love me? I know thou wilt say 'Ay,' And I will take thy word: ", ciphers, 0, 3);
	checkWord("Supper is done, and we shall come too late. ROMEO I fear, too early: for my mind misgives Some consequence yet hanging ", ciphers, 0, 9);
	checkWord("Must be my convoy in the secret night. Farewell; be trusty, and I'll quit thy pains: Farewell; commend me to thy mistress", ciphers, 0, 4);
	checkWord("May prove a beauteous flower when next we meet. Good night, good night! as sweet repose and rest Come to thy heart as that ", ciphers, 0, 2);
	checkWord("The ship, sir, the slip; can you not conceive? ROMEO Pardon, good Mercutio, my business was great; and in such a case as mine ", ciphers, 0, 10);
	checkWord("After the prompter, for our entrance: But let them measure us by what they will; We'll measure them a measure, and be gone. ROMEO ", ciphers, 0, 6);
	checkWord("Because their breaths with sweetmeats tainted are: Sometime she gallops o'er a courtier's nose, And then dreams he of smelling out ", ciphers, 0, 7);
	checkWord("To see, now, how a jest shall come about! I warrant, an I should live a thousand years, I never should forget it: 'Wilt thou not, Jul", ciphers, 0, 17);
	checkWord("down, an a' were lustier than he is, and twenty such Jacks; and if I cannot, I'll find those that shall. Scurvy knave! I am none of his ", ciphers, 0, 16);
	checkWord("Because their breaths with sweetmeats tainted are: Sometime she gallops o'er a courtier's nose, And then dreams he of smelling out a suit", ciphers, 0, 7);
	checkWord("May prove a beauteous flower when next we meet. Good night, good night! as sweet repose and rest Come to thy heart as that within my breast", ciphers, 0, 2);
	checkWord("down, an a' were lustier than he is, and twenty such Jacks; and if I cannot, I'll find those that shall. Scurvy knave! I am none of his flirt", ciphers, 0, 16);
	checkWord("The ship, sir, the slip; can you not conceive? ROMEO Pardon, good Mercutio, my business was great; and in such a case as mine a man may strain ", ciphers, 0, 10);
	checkWord("May prove a beauteous flower when next we meet. Good night, good night! as sweet repose and rest Come to thy heart as that within my breast! ROMEO", ciphers, 0, 2);
	checkWord("Because their breaths with sweetmeats tainted are: Sometime she gallops o'er a courtier's nose, And then dreams he of smelling out a suit; And sometime ", ciphers, 0, 7);
	checkWord("down, an a' were lustier than he is, and twenty such Jacks; and if I cannot, I'll find those that shall. Scurvy knave! I am none of his flirt-gills; I am ", ciphers, 0, 16);
	checkWord("What I have spoke: but farewell compliment! Dost thou love me? I know thou wilt say 'Ay,' And I will take thy word: yet if thou swear'st, Thou mayst prove ", ciphers, 0, 3);
	checkWord("down, an a' were lustier than he is, and twenty such Jacks; and if I cannot, I'll find those that shall. Scurvy knave! I am none of his flirt-gills; I am none of his ", ciphers, 0, 16);
	checkWord("Because their breaths with sweetmeats tainted are: Sometime she gallops o'er a courtier's nose, And then dreams he of smelling out a suit; And sometime comes she with ", ciphers, 0, 7);
	checkWord("What I have spoke: but farewell compliment! Dost thou love me? I know thou wilt say 'Ay,' And I will take thy word: yet if thou swear'st, Thou mayst prove false; at lovers", ciphers, 0, 3);
}
