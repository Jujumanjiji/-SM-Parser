#include <iostream>
#include <vector>
#include <fstream>	// Stream class to read and write from/to files
#include <string>	// function getline...
#include <string.h>
#include <stdio.h>
#include <stdlib.h> // strtof //
#include <sstream>
#include <map>
#include <cstdlib> strtol(s.c_str(),0,10);
#include "string"
#include <ctype.h>
#include <iomanip>

using namespace std;

/* ------------------------------------------*/
/* FUNCTION THAT CONVERT A STRING TO A FLOAT */
/* ------------------------------------------*/
float convertStringToFloat(string a) {
	float value = strtof((a).c_str(), 0);
	return value;
}

struct NoteData
{
	vector<vector<NoteData> > bars;
};

/*-------------------------------------------------*/
/* FUNCTION THAT REMOVES WHITESPACES FROM A STRING */
/*-------------------------------------------------*/
std::string deleteSpaces(const std::string &str)
{
	std::string returnString;

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
			continue;

		returnString += str[i];
	}

	return returnString;
}

/*--------------------------------*/
/* SM FILE'S MAIN DATAS STRUCTURE */
/*--------------------------------*/
struct metaData
{
	//Is the song's structure valid ?
	bool valid;

	//The title, subtitle and Artist for the song
	string title;
	string subtitle;
	string artist;
	string credit;
	string selectable;

	//The file paths for the related images and song media
	string bannerPath;
	string backgroundPath;
	string musicPath;
	string cdTitle;

	//The offset that the song starts at compared to the step info
	float offset;
	int musicBytes;
	//The start and length of the sample that is played when selecting a song
	float sampleStart;
	float sampleLength;
	float musicLength;

	//The bpm the song is played at
	float beat_bpm;
	float bpm;
	float beat_stop;
	float sec;

	//The note data for each difficulty
	NoteData beginner;
	bool beginnerExists;
	NoteData easy;
	bool easyExists;
	NoteData medium;
	bool mediumExists;
	NoteData hard;
	bool hardExists;
	NoteData challenge;
	bool challengeExists;

	bool inNotes = false;

	metaData()
	{
		valid = true;
		beginnerExists = false;
		easyExists = false;
		mediumExists = false;
		hardExists = false;
		challengeExists = false;
	};
} metaData_var;

/*-----------------*/
/* Notes structure */
/*-----------------*/

struct Notes
{
	string notesTypes;
	string description;
	string difficultyClass;
	int difficultyMeter;
	float radarValues;

	bool left;
	bool right;
	bool up;
	bool down;
}notesData_var;

/* ------------------------------------------------------*/
/* HEADER TAGS PARSING FUNCTION (Title, Artist, BPMs...) */
/* ------------------------------------------------------*/

bool ParseHeader(const std::string& line)
{
	if (line[0] == '//')
	{
		return true;
	}
	else if (line[0] == '#')
	{
		std::string key = line.substr(1, line.find(':') - 1);

		if (key == "TITLE") // OK
		{
			size_t idx = line.find_first_of(':') + 1;
			metaData_var.title = line.substr(idx, line.size() - idx - 1);
			cout << "Title : " << metaData_var.title << ";" << endl;
		}

		else if (key == "SUBTITLE") // OK
		{
			size_t idx = line.find_first_of(':') + 1;
			metaData_var.subtitle = line.substr(idx, line.size() - idx - 1);
			cout << "Subtitle : " << metaData_var.subtitle << ";" << endl;
		}

		else if (key == "ARTIST") // OK
		{
			size_t idx = line.find_first_of(':') + 1;
			metaData_var.artist = line.substr(idx, line.size() - idx - 1);
			cout << "Artist : " << metaData_var.artist << ";" << endl;
		}

		else if (key == "CREDIT") // OK
		{
			size_t idx = line.find_first_of(':') + 1;
			metaData_var.credit = line.substr(idx, line.size() - idx - 1);
			cout << "Credit : " << metaData_var.credit << ";" << endl;
		}

		else if (key == "BANNER") // OK
		{
			size_t idx = line.find_first_of(':') + 1;
			metaData_var.bannerPath = line.substr(idx, line.size() - idx - 1);
			cout << "Banner : " << metaData_var.bannerPath << ";" << endl;
		}

		else if (key == "BACKGROUND") // OK
		{
			size_t idx = line.find_first_of(':') + 1;
			metaData_var.backgroundPath = line.substr(idx, line.size() - idx - 1);
			cout << "Background : " << metaData_var.backgroundPath << ";" << endl;
		}

		else if (key == "CDTITLE") // OK
		{
			size_t idx = line.find_first_of(':') + 1;
			metaData_var.cdTitle = line.substr(idx, line.size() - idx - 1);
			cout << "CD Title : " << metaData_var.cdTitle << ";" << endl;
		}

		else if (key == "MUSIC") // OK
		{
			size_t idx = line.find_first_of(':') + 1;
			metaData_var.musicPath = line.substr(idx, line.size() - idx - 1);
			cout << "Music : " << metaData_var.musicPath << ";" << endl;
		}

		else if (key == "MUSICBYTES") // OK
		{
			size_t idx = line.find_first_of(':') + 1;
			string musicbytes = line.substr(idx, line.size() - idx - 1);
			metaData_var.musicBytes = atoi(musicbytes.c_str());
			cout << "Music Bytes : " << metaData_var.musicBytes << ";" << endl;
		}

		else if (key == "MUSICLENGTH") // OK
		{
			size_t idx = line.find_first_of(':') + 1;
			string musicLength = line.substr(idx, line.size() - idx - 1);
			const char* pMusicLength = musicLength.c_str();
			char* pEnd;
			metaData_var.musicLength = strtof(pMusicLength, &pEnd);
			cout << "Music Length : " << metaData_var.musicLength << ";" << endl;
		}

		else if (key == "OFFSET") // OK
		{
			size_t idx = line.find_first_of(':') + 1;
			string offset = line.substr(idx, line.size() - idx - 1);
			const char* pOffset = offset.c_str();
			char* pEnd;
			metaData_var.offset = strtof(pOffset, &pEnd);
			cout << "Offset : " << fixed << setprecision(3) << metaData_var.offset << ";" << endl;
		}

		else if (key == "SAMPLESTART") // OK
		{
			size_t idx = line.find_first_of(':') + 1;
			string sampleStart = line.substr(idx, line.size() - idx - 1);
			const char* pSampleStart = sampleStart.c_str();
			char* pEnd;
			metaData_var.sampleStart = strtof(pSampleStart, &pEnd);
			cout << "Sample Start : " << fixed << setprecision(3) << metaData_var.sampleStart << ";" << endl;
		}

		else if (key == "SAMPLELENGTH") // OK
		{
			size_t idx = line.find_first_of(':') + 1;
			string sampleLength = line.substr(idx, line.size() - idx - 1);
			const char* pSampleLength = sampleLength.c_str();
			char* pEnd;
			metaData_var.sampleLength = strtof(pSampleLength, &pEnd);
			cout << "Sample Length : " << fixed << setprecision(3) << metaData_var.sampleLength << ";" << endl;
		}

		else if (key == "SELECTABLE") // OK
		{
			size_t idx = line.find_first_of(':') + 1;
			metaData_var.selectable = line.substr(idx, line.size() - idx - 1);
			cout << "Selectable : " << metaData_var.selectable << ";" << endl;
		}

		else if (key == "BPMS") // OK
		{
			size_t idx = line.find_first_of(':') + 1;
			string bpms = line.substr(idx, line.size() - idx - 1);
			map<float, float> values = {};
			stringstream str(bpms);
			float i;
			while (str >> i)
			{
				str.ignore();
				str >> values[i];

				if (str.peek() == ',')
					str.ignore();
			}
			for (auto iter = values.begin(); iter != values.end(); iter++)
			{
				metaData_var.beat_bpm = iter->first;
				metaData_var.bpm = iter->second;
				cout << "BPMS : " << fixed << setprecision(3) << metaData_var.beat_bpm << " = " << fixed << setprecision(3) << metaData_var.bpm << ";" << endl;
			}
		}

		else if (key == "STOPS") // OK
		{
			size_t idx = line.find_first_of(':') + 1;
			string stops = line.substr(idx, line.size() - idx - 1);
			map<float, float> values = {};
			stringstream str(stops);
			float i;
			while (str >> i)
			{
				str.ignore();
				str >> values[i];

				if (str.peek() == ',')
					str.ignore();
			}
			for (auto iter = values.begin(); iter != values.end(); iter++)
			{
				metaData_var.beat_stop = iter->first;
				metaData_var.sec = iter->second;
				cout << "STOPS : " << fixed << setprecision(3) << iter->first << " = " << fixed << setprecision(3) << iter->second << ";" << endl;
			}
		}

		else if (key == "NOTES") // OK
		{
			return false;
		}

		return true;


		/*else if (key == "BGCHANGES") // NOT IMPLEMENTED YET
		{
		size_t idx = line.find_first_of(':') + 1;
		string bgChanges = line.substr(idx,line.size()- idx - 1);
		int pos = bgChanges.find_first_of(',');
		string test1 = bgChanges.substr(0, pos);
		string test2 = bgChanges.substr(pos+1);

		cout << "BGCHANGES : " << test1 << "," << test2 << endl;
		}*/
	}
}

/* -------------------------------------------------------*/
/* CHART DATA PARSING FUNCTION (Difficulty, Notes data...)*/
/* -------------------------------------------------------*/

void ParseNotes(string& line)
{
	if (line.length() != 0)
	{
		string key = line.substr(1, line.find_first_of(':') - 1);
	}
}

/*if (newLine[0] == '#')
{
string key = newLine.substr(1, newLine.find_first_of(':') - 1);

if (key == "NOTES")
{
deleteSpaces(newLine);
cout << newLine << endl;
}
}*/

/* ----------------------------------------------------*/
/* MAIN FUNCTION THAT READ THE SM FILE LINES PER LINES */
/* ----------------------------------------------------*/

int main()
{
	string line;
	string newLine;
	bool isHeader = true;
	ifstream file("Samples/ATB - 9 PM (Till I Come).sm");
	if (file.is_open()) {
		while (getline(file, line))
		{
			if (isHeader) {
				isHeader = ParseHeader(line);
			}
			else {
				ParseNotes(line);
			}
		}
		file.close();
	}
	else {
		cout << "Cannot Open SM file" << '\n';
		cin.get();
	}

	ParseNotes(newLine);
	return 0;

	/*string myString = "100";
	float myValue = convertToFloat(myString);
	cout << myValue <<endl;*/
};
