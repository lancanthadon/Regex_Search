#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <cmath>

using namespace std;

// using a class to hold files and content
class File
{
   public:
        string filename;
        vector<string> content;
};

// this section grabs all existing files in the current directory (including all the files in the subdirectories)

void Getfiles(const char *name, vector<File> &files)
{
	File s;
	DIR *streamdir;
    	struct dirent *prent;

    	if (!(streamdir = opendir(name)))
        	return;

    	while ((prent = readdir(streamdir)) != NULL) 
	{
		char path[1024];
        	if (prent->d_type == DT_DIR) 
		{
            		if (strcmp(prent->d_name, ".") == 0 || strcmp(prent->d_name, "..") == 0)
               			continue;
            		snprintf(path, sizeof(path), "%s/%s", name, prent->d_name);
            		Getfiles(path, files);
        	} 
		else 
		{
			snprintf(path, sizeof(path), "%s/%s", name, prent->d_name);
			s.filename = path;
			files.push_back(s);
		}
    	}
}

// this section grabs all the content from the files by line

void Getcontent(vector<File> &files)
{
	string line;
	for (int i=0; i<files.size(); i++)
	{
		ifstream input(files[i].filename);
		while(getline(input,line))
		{
			istringstream record(line);
			files[i].content.push_back(line);
		}
	}
}

void WordCount(vector<File> &files)
{
	cout << "////////////////////Part 1:" << endl << "Enter a search word" << endl;
	string word;
	cin >> word;
	for (int i=0; i<files.size(); i++)
        {
		int count=0;
		int pos;
		for(int j=0; j<files[i].content.size(); j++)
		{
			pos = files[i].content[j].find(word, 0);
	     		while (pos != string::npos)
			{
			   ++count;
			   pos = files[i].content[j].find(word, pos+1);
			}
		}
		 cout << word << " occurs " << count << " times in " << files[i].filename << endl;
        }
}

void LineCount(vector<File> &files)
{
	cout << "////////////////////Part 2:" << endl << "Enter a search word" << endl;
	string word;
	cin >> word;
	for (int i=0; i<files.size(); i++)
	{
		for (int j=0; j<files[i].content.size(); j++)
		{
			int t = files[i].content[j].find(word, 0);
			if (t != string::npos)
			{
				cout << word << " occurs on line " << j <<" in file " << files[i].filename << endl << files[i].content[j] << endl << endl;
			t=0;
			}
		}
	}
	
}

void WordFreq(vector<File> &files)
{
	cout << "////////////////////Part 4:" << endl;
	vector<string> words;
	string word;
	for (int i=0; i<files.size(); i++)
        {
                int pos;
                for(int j=0; j<files[i].content.size(); j++)
                {
		     std::stringstream iss;
		     iss << files[i].content[j];
                     while (iss >> word)
                     {
			   words.push_back(word);
                     }
                }
        }
	sort(words.begin(), words.end(), greater<string>());
	int count = 1;
	for (int i=0; i<words.size(); i++)
	{
	        if (words[i] == words[i+1])
	           ++count;
		else
		{
		   cout << words[i] << " occurs " << count << " times" << endl;
		   count = 1;
		} 
	}
}

void CheckBalanced(vector<File> &files)
{
	cout << "////////////////////Part 5:" << endl;
	int par;
        int brack;
        int curl;

	for (int i=0; i<files.size(); i++)
	{
	    par=0;
            brack=0;
            curl=0;
	    int par_line;
	    int brack_line;
            int curl_line;

		for (int j=0; j<files[i].content.size(); j++)
		{
		   for (int k=0; k<files[i].content[j].size(); k++)
		   {
			if (files[i].content[j][k] == '(')
			{
				 ++par;
				 par_line = j;
			}
			else if (files[i].content[j][k] == ')')
			{
				 --par;
				 par_line = j;
			}
			else if (files[i].content[j][k] == '[')
                        {       
				 ++brack;
				 brack_line = j;
			}
			else if (files[i].content[j][k] == ']')
                        {
			         --brack;
				 brack_line = j;
			}
			else if (files[i].content[j][k] == '{')
			{
                                 ++curl;
				 curl_line = j;
			}
			else if (files[i].content[j][k] == '}')
                        {       
				 --curl;
				 curl_line = j;
			}
		   }
		}
		if (par != 0)
			cout << files[i].filename << endl << "unbalanced on line " << par_line << endl << files[i].content[par_line] << endl;
		if (brack != 0)
                        cout << files[i].filename << endl << "unbalanced on line " << brack_line << endl << files[i].content[brack_line] << endl;
		if (curl != 0)
                        cout << files[i].filename << endl << "unbalanced on line " << curl_line << endl << files[i].content[curl_line] << endl;
 
	}
}

string Replace(string pattern)
{
        size_t pos = 0;
        while((pos = pattern.find("?",pos)) != string::npos) {
                pattern.replace(pos, 1, ".+");
                pos+=2;
        }
        pos = 0;
        while((pos = pattern.find("*",pos)) != string::npos) {
                pattern.replace(pos, 1, ".*");
                pos+=2;
        }
        return pattern;
}

bool Match(string line, string pattern)
{
        string pattern2 = Replace(pattern);
        regex pat(pattern2);
        bool result = regex_search(line, pat);
	return result;
}

void FindPattern(vector<File> &files, string pattern)
{
	for (int i=0; i<files.size(); i++)
	{
		for (int j=0; j<files[i].content.size(); j++)
		{ 
			Match(files[i].content[j], pattern) ? cout << files[i].filename << " line " << j << endl << files[i].content[j] << endl : cout << "";
			
		}
	}
}

void TFIDF(vector<File> &files)
{
        cout << "///////////////////Part 6:" << endl << "Enter a search word" << endl;	
	double idf;
	double doc_num=0;
	double w_doc=0;
        string word;
        cin >> word;
        for (int i=0; i<files.size(); i++)
        {
                int count=0;
                int pos;
		++doc_num;
                for(int j=0; j<files[i].content.size(); j++)
                {
                        pos = files[i].content[j].find(word, 0);
                        while (pos != string::npos)
                        {
                           ++count;
                           pos = files[i].content[j].find(word, pos+1);
                        }
                }
		if (count)
			++w_doc;
        }

	idf = log(doc_num/w_doc);

	for (int i=0; i<files.size(); i++)
        {
		double tf_idf=0;
		double tf=0;
		double cnt=0;
		double total=0;
                int pos;
                for(int j=0; j<files[i].content.size(); j++)
                {
		        pos = files[i].content[j].find(word, 0);
                        while (pos != string::npos)
                        {
                           ++cnt;
                           pos = files[i].content[j].find(word, pos+1);
                        }

		     for (int k=0; k<files[i].content[j].size(); k++)
		     {
			++total;
		     }
		     
                }
		tf = cnt/total;
		tf_idf = tf*idf;
		if (tf_idf > 0.04)
		cout << files[i].filename << " " << tf_idf << endl;
        }
}

int main() 
{
	vector<File> files;
    	Getfiles(".", files);
	files.erase(files.end()); // this line just deletes "a.out" (execution file)
	Getcontent(files);
	WordCount(files);
	cout << endl;

	LineCount(files);
	cout << endl;

	string pattern;
        cout << "////////////////////Part 3: " << endl;
        cout << "Enter a search pattern using * and/or ?" << endl;
        cin >> pattern;
        FindPattern(files, pattern);
	cout << endl;

	cin.ignore();
	cout << "Hit Enter to run Part 4" << endl;
	cin.ignore();
	WordFreq(files);
	cout << endl;

	cout << "Hit Enter to run Part 5" << endl;
	cin.ignore();
	CheckBalanced(files);
	cout << endl;

	TFIDF(files);

	return 0;
}
