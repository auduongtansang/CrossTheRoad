#include "Data.h"

bool SaveData(char *s, People people, Peoples finished, Cars cars, Buffer buffer, bool isAlive)
{
	if (s == NULL)
	{
		return false;
	}

	ofstream f;
	f.open(s, ios::out || ios::binary);

	f.write((char*)&people, sizeof(People));

	int nFinised = (int)(finished.size());
	f.write((char*)&nFinised, sizeof(int));
	for (int i = 0; i < nFinised; i++)
	{
		f.write((char*)&finished[i], sizeof(People));
	}

	int nCars, sCars;
	nCars = (int)(cars.size());
	sCars = (int)(cars[0].node.size());
	f.write((char*)&nCars, sizeof(int));
	f.write((char*)&sCars, sizeof(int));
	for (int i = 0; i < nCars; i++)
	{
		f.write((char*)&cars[i].character, sizeof(char));
		f.write((char*)&cars[i].speed, sizeof(int));
		for (int j = 0; j < sCars; j++)
		{
			f.write((char*)&cars[i].node[j], sizeof(COORD));
		}
	}

	int consoleHeight, consoleWidth;
	BufferSize(consoleWidth, consoleHeight);
	f.write((char*)&consoleHeight, sizeof(int));
	f.write((char*)&consoleWidth, sizeof(int));
	for (int i = 0; i < consoleWidth; i++)
	{
		for (int j = 0; j < consoleHeight; j++)
		{
			f.write((char*)&buffer[i][j], sizeof(char));
		}
	}

	f.write((char*)&isAlive, sizeof(bool));
	f.close();
	return true;
}

bool LoadData(char *s, People &people, Peoples &finished, Cars &cars, Buffer &buffer, bool &isAlive)
{
	if (s == NULL)
	{
		return false;
	}

	ifstream f;
	f.open(s, ios::in || ios::binary);
	if (f.eof())
	{
		f.close();
		return false;
	}

	f.read((char*)&people, sizeof(People));

	int nFinised = 0;
	f.read((char*)&nFinised, sizeof(int));
	finished.resize(nFinised);
	for (int i = 0; i < nFinised; i++)
	{
		f.read((char*)&finished[i], sizeof(People));
	}

	int nCars = 0, sCars = 0;
	f.read((char*)&nCars, sizeof(int));
	f.read((char*)&sCars, sizeof(int));
	cars.resize(nCars);
	for (int i = 0; i < nCars; i++)
	{
		f.read((char*)&cars[i].character, sizeof(char));
		f.read((char*)&cars[i].speed, sizeof(int));
		cars[i].node.resize(sCars);
		for (int j = 0; j < sCars; j++)
		{
			f.read((char*)&cars[i].node[j], sizeof(COORD));
		}
	}

	int consoleHeight = 0, consoleWidth = 0;
	f.read((char*)&consoleHeight, sizeof(int));
	f.read((char*)&consoleWidth, sizeof(int));
	buffer.resize(consoleWidth);
	for (int i = 0; i < consoleWidth; i++)
	{
		buffer[i].resize(consoleHeight);
		for (int j = 0; j < consoleHeight; j++)
		{
			f.read((char*)&buffer[i][j], sizeof(char));
		}
	}

	f.read((char*)&isAlive, sizeof(bool));
	f.close();
	return true;
}